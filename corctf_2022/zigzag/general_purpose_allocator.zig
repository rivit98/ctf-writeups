//! # General Purpose Allocator
//!
//! ## Design Priorities
//!
//! ### `OptimizationMode.debug` and `OptimizationMode.release_safe`:
//!
//!  * Detect double free, and emit stack trace of:
//!    - Where it was first allocated
//!    - Where it was freed the first time
//!    - Where it was freed the second time
//!
//!  * Detect leaks and emit stack trace of:
//!    - Where it was allocated
//!
//!  * When a page of memory is no longer needed, give it back to resident memory
//!    as soon as possible, so that it causes page faults when used.
//!
//!  * Do not re-use memory slots, so that memory safety is upheld. For small
//!    allocations, this is handled here; for larger ones it is handled in the
//!    backing allocator (by default `std.heap.page_allocator`).
//!
//!  * Make pointer math errors unlikely to harm memory from
//!    unrelated allocations.
//!
//!  * It's OK for these mechanisms to cost some extra overhead bytes.
//!
//!  * It's OK for performance cost for these mechanisms.
//!
//!  * Rogue memory writes should not harm the allocator's state.
//!
//!  * Cross platform. Operates based on a backing allocator which makes it work
//!    everywhere, even freestanding.
//!
//!  * Compile-time configuration.
//!
//! ### `OptimizationMode.release_fast` (note: not much work has gone into this use case yet):
//!
//!  * Low fragmentation is primary concern
//!  * Performance of worst-case latency is secondary concern
//!  * Performance of average-case latency is next
//!  * Finally, having freed memory unmapped, and pointer math errors unlikely to
//!    harm memory from unrelated allocations are nice-to-haves.
//!
//! ### `OptimizationMode.release_small` (note: not much work has gone into this use case yet):
//!
//!  * Small binary code size of the executable is the primary concern.
//!  * Next, defer to the `.release_fast` priority list.
//!
//! ## Basic Design:
//!
//! Small allocations are divided into buckets:
//!
//! ```
//! index obj_size
//! 0     1
//! 1     2
//! 2     4
//! 3     8
//! 4     16
//! 5     32
//! 6     64
//! 7     128
//! 8     256
//! 9     512
//! 10    1024
//! 11    2048
//! ```
//!
//! The main allocator state has an array of all the "current" buckets for each
//! size class. Each slot in the array can be null, meaning the bucket for that
//! size class is not allocated. When the first object is allocated for a given
//! size class, it allocates 1 page of memory from the OS. This page is
//! divided into "slots" - one per allocated object. Along with the page of memory
//! for object slots, as many pages as necessary are allocated to store the
//! BucketHeader, followed by "used bits", and two stack traces for each slot
//! (allocation trace and free trace).
//!
//! The "used bits" are 1 bit per slot representing whether the slot is used.
//! Allocations use the data to iterate to find a free slot. Frees assert that the
//! corresponding bit is 1 and set it to 0.
//!
//! Buckets have prev and next pointers. When there is only one bucket for a given
//! size class, both prev and next point to itself. When all slots of a bucket are
//! used, a new bucket is allocated, and enters the doubly linked list. The main
//! allocator state tracks the "current" bucket for each size class. Leak detection
//! currently only checks the current bucket.
//!
//! Resizing detects if the size class is unchanged or smaller, in which case the same
//! pointer is returned unmodified. If a larger size class is required,
//! `error.OutOfMemory` is returned.
//!
//! Large objects are allocated directly using the backing allocator and their metadata is stored
//! in a `std.HashMap` using the backing allocator.

const std = @import("std");
const builtin = @import("builtin");
const log = std.log.scoped(.gpa);
const math = std.math;
const assert = std.debug.assert;
const mem = std.mem;
const Allocator = std.mem.Allocator;
const page_size = std.mem.page_size;
const StackTrace = std.builtin.StackTrace;

/// Integer type for pointing to slots in a small allocation
const SlotIndex = std.meta.Int(.unsigned, math.log2(page_size) + 1);

const default_test_stack_trace_frames: usize = if (builtin.is_test) 8 else 4;
const default_sys_stack_trace_frames: usize = if (std.debug.sys_can_stack_trace) default_test_stack_trace_frames else 0;
const default_stack_trace_frames: usize = switch (builtin.mode) {
    .Debug => default_sys_stack_trace_frames,
    else => 0,
};

pub const Config = struct {
    /// Number of stack frames to capture.
    stack_trace_frames: usize = default_stack_trace_frames,

    /// If true, the allocator will have two fields:
    ///  * `total_requested_bytes` which tracks the total allocated bytes of memory requested.
    ///  * `requested_memory_limit` which causes allocations to return `error.OutOfMemory`
    ///    when the `total_requested_bytes` exceeds this limit.
    /// If false, these fields will be `void`.
    enable_memory_limit: bool = false,

    /// Whether to enable safety checks.
    safety: bool = std.debug.runtime_safety,

    /// Whether the allocator may be used simultaneously from multiple threads.
    thread_safe: bool = !builtin.single_threaded,

    /// What type of mutex you'd like to use, for thread safety.
    /// when specfied, the mutex type must have the same shape as `std.Thread.Mutex` and
    /// `DummyMutex`, and have no required fields. Specifying this field causes
    /// the `thread_safe` field to be ignored.
    ///
    /// when null (default):
    /// * the mutex type defaults to `std.Thread.Mutex` when thread_safe is enabled.
    /// * the mutex type defaults to `DummyMutex` otherwise.
    MutexType: ?type = null,

    /// This is a temporary debugging trick you can use to turn segfaults into more helpful
    /// logged error messages with stack trace details. The downside is that every allocation
    /// will be leaked, unless used with retain_metadata!
    never_unmap: bool = false,

    /// This is a temporary debugging aid that retains metadata about allocations indefinitely.
    /// This allows a greater range of double frees to be reported. All metadata is freed when
    /// deinit is called. When used with never_unmap, deliberately leaked memory is also freed
    /// during deinit. Currently should be used with never_unmap to avoid segfaults.
    /// TODO https://github.com/ziglang/zig/issues/4298 will allow use without never_unmap
    retain_metadata: bool = false,

    /// Enables emitting info messages with the size and address of every allocation.
    verbose_log: bool = false,
};

pub fn GeneralPurposeAllocator(comptime config: Config) type {
    return struct {
        backing_allocator: Allocator = std.heap.page_allocator,
        buckets: [small_bucket_count]?*BucketHeader = [1]?*BucketHeader{null} ** small_bucket_count,
        large_allocations: LargeAllocTable = .{},
        empty_buckets: if (config.retain_metadata) ?*BucketHeader else void =
            if (config.retain_metadata) null else {},

        total_requested_bytes: @TypeOf(total_requested_bytes_init) = total_requested_bytes_init,
        requested_memory_limit: @TypeOf(requested_memory_limit_init) = requested_memory_limit_init,

        mutex: @TypeOf(mutex_init) = mutex_init,

        const Self = @This();

        const total_requested_bytes_init = if (config.enable_memory_limit) @as(usize, 0) else {};
        const requested_memory_limit_init = if (config.enable_memory_limit) @as(usize, math.maxInt(usize)) else {};

        const mutex_init = if (config.MutexType) |T|
            T{}
        else if (config.thread_safe)
            std.Thread.Mutex{}
        else
            DummyMutex{};

        const DummyMutex = struct {
            fn lock(_: *DummyMutex) void {}
            fn unlock(_: *DummyMutex) void {}
        };

        const stack_n = config.stack_trace_frames;
        const one_trace_size = @sizeOf(usize) * stack_n;
        const traces_per_slot = 2;

        pub const Error = mem.Allocator.Error;

        const small_bucket_count = math.log2(page_size);
        const largest_bucket_object_size = 1 << (small_bucket_count - 1);

        const LargeAlloc = struct {
            bytes: []u8,
            requested_size: if (config.enable_memory_limit) usize else void,
            stack_addresses: [trace_n][stack_n]usize,
            freed: if (config.retain_metadata) bool else void,
            ptr_align: if (config.never_unmap and config.retain_metadata) u29 else void,

            const trace_n = if (config.retain_metadata) traces_per_slot else 1;

            fn dumpStackTrace(self: *LargeAlloc, trace_kind: TraceKind) void {
                std.debug.dumpStackTrace(self.getStackTrace(trace_kind));
            }

            fn getStackTrace(self: *LargeAlloc, trace_kind: TraceKind) std.builtin.StackTrace {
                assert(@enumToInt(trace_kind) < trace_n);
                const stack_addresses = &self.stack_addresses[@enumToInt(trace_kind)];
                var len: usize = 0;
                while (len < stack_n and stack_addresses[len] != 0) {
                    len += 1;
                }
                return .{
                    .instruction_addresses = stack_addresses,
                    .index = len,
                };
            }

            fn captureStackTrace(self: *LargeAlloc, ret_addr: usize, trace_kind: TraceKind) void {
                assert(@enumToInt(trace_kind) < trace_n);
                const stack_addresses = &self.stack_addresses[@enumToInt(trace_kind)];
                collectStackTrace(ret_addr, stack_addresses);
            }
        };
        const LargeAllocTable = std.AutoHashMapUnmanaged(usize, LargeAlloc);

        // Bucket: In memory, in order:
        // * BucketHeader
        // * bucket_used_bits: [N]u8, // 1 bit for every slot; 1 byte for every 8 slots
        // * stack_trace_addresses: [N]usize, // traces_per_slot for every allocation

        const BucketHeader = struct {
            prev: *BucketHeader,
            next: *BucketHeader,
            page: [*]align(page_size) u8,
            alloc_cursor: SlotIndex,
            used_count: SlotIndex,

            fn usedBits(bucket: *BucketHeader, index: usize) *u8 {
                return @intToPtr(*u8, @ptrToInt(bucket) + @sizeOf(BucketHeader) + index);
            }

            fn stackTracePtr(
                bucket: *BucketHeader,
                size_class: usize,
                slot_index: SlotIndex,
                trace_kind: TraceKind,
            ) *[stack_n]usize {
                const start_ptr = @ptrCast([*]u8, bucket) + bucketStackFramesStart(size_class);
                const addr = start_ptr + one_trace_size * traces_per_slot * slot_index +
                    @enumToInt(trace_kind) * @as(usize, one_trace_size);
                return @ptrCast(*[stack_n]usize, @alignCast(@alignOf(usize), addr));
            }

            fn captureStackTrace(
                bucket: *BucketHeader,
                ret_addr: usize,
                size_class: usize,
                slot_index: SlotIndex,
                trace_kind: TraceKind,
            ) void {
                // Initialize them to 0. When determining the count we must look
                // for non zero addresses.
                const stack_addresses = bucket.stackTracePtr(size_class, slot_index, trace_kind);
                collectStackTrace(ret_addr, stack_addresses);
            }
        };

        pub fn allocator(self: *Self) Allocator {
            return Allocator.init(self, alloc, resize, free);
        }

        fn bucketStackTrace(
            bucket: *BucketHeader,
            size_class: usize,
            slot_index: SlotIndex,
            trace_kind: TraceKind,
        ) StackTrace {
            const stack_addresses = bucket.stackTracePtr(size_class, slot_index, trace_kind);
            var len: usize = 0;
            while (len < stack_n and stack_addresses[len] != 0) {
                len += 1;
            }
            return StackTrace{
                .instruction_addresses = stack_addresses,
                .index = len,
            };
        }

        fn bucketStackFramesStart(size_class: usize) usize {
            return mem.alignForward(
                @sizeOf(BucketHeader) + usedBitsCount(size_class),
                @alignOf(usize),
            );
        }

        fn bucketSize(size_class: usize) usize {
            const slot_count = @divExact(page_size, size_class);
            return bucketStackFramesStart(size_class) + one_trace_size * traces_per_slot * slot_count;
        }

        fn usedBitsCount(size_class: usize) usize {
            const slot_count = @divExact(page_size, size_class);
            if (slot_count < 8) return 1;
            return @divExact(slot_count, 8);
        }

        fn detectLeaksInBucket(
            bucket: *BucketHeader,
            size_class: usize,
            used_bits_count: usize,
        ) bool {
            var leaks = false;
            var used_bits_byte: usize = 0;
            while (used_bits_byte < used_bits_count) : (used_bits_byte += 1) {
                const used_byte = bucket.usedBits(used_bits_byte).*;
                if (used_byte != 0) {
                    var bit_index: u3 = 0;
                    while (true) : (bit_index += 1) {
                        const is_used = @truncate(u1, used_byte >> bit_index) != 0;
                        if (is_used) {
                            const slot_index = @intCast(SlotIndex, used_bits_byte * 8 + bit_index);
                            const stack_trace = bucketStackTrace(bucket, size_class, slot_index, .alloc);
                            const addr = bucket.page + slot_index * size_class;
                            log.err("memory address 0x{x} leaked: {s}", .{
                                @ptrToInt(addr), stack_trace,
                            });
                            leaks = true;
                        }
                        if (bit_index == math.maxInt(u3))
                            break;
                    }
                }
            }
            return leaks;
        }

        /// Emits log messages for leaks and then returns whether there were any leaks.
        pub fn detectLeaks(self: *Self) bool {
            var leaks = false;
            for (self.buckets) |optional_bucket, bucket_i| {
                const first_bucket = optional_bucket orelse continue;
                const size_class = @as(usize, 1) << @intCast(math.Log2Int(usize), bucket_i);
                const used_bits_count = usedBitsCount(size_class);
                var bucket = first_bucket;
                while (true) {
                    leaks = detectLeaksInBucket(bucket, size_class, used_bits_count) or leaks;
                    bucket = bucket.next;
                    if (bucket == first_bucket)
                        break;
                }
            }
            var it = self.large_allocations.valueIterator();
            while (it.next()) |large_alloc| {
                if (config.retain_metadata and large_alloc.freed) continue;
                const stack_trace = large_alloc.getStackTrace(.alloc);
                log.err("memory address 0x{x} leaked: {s}", .{
                    @ptrToInt(large_alloc.bytes.ptr), stack_trace,
                });
                leaks = true;
            }
            return leaks;
        }

        fn freeBucket(self: *Self, bucket: *BucketHeader, size_class: usize) void {
            const bucket_size = bucketSize(size_class);
            const bucket_slice = @ptrCast([*]align(@alignOf(BucketHeader)) u8, bucket)[0..bucket_size];
            self.backing_allocator.free(bucket_slice);
        }

        fn freeRetainedMetadata(self: *Self) void {
            if (config.retain_metadata) {
                if (config.never_unmap) {
                    // free large allocations that were intentionally leaked by never_unmap
                    var it = self.large_allocations.iterator();
                    while (it.next()) |large| {
                        if (large.value_ptr.freed) {
                            self.backing_allocator.rawFree(large.value_ptr.bytes, large.value_ptr.ptr_align, @returnAddress());
                        }
                    }
                }
                // free retained metadata for small allocations
                if (self.empty_buckets) |first_bucket| {
                    var bucket = first_bucket;
                    while (true) {
                        const prev = bucket.prev;
                        if (config.never_unmap) {
                            // free page that was intentionally leaked by never_unmap
                            self.backing_allocator.free(bucket.page[0..page_size]);
                        }
                        // alloc_cursor was set to slot count when bucket added to empty_buckets
                        self.freeBucket(bucket, @divExact(page_size, bucket.alloc_cursor));
                        bucket = prev;
                        if (bucket == first_bucket)
                            break;
                    }
                    self.empty_buckets = null;
                }
            }
        }

        pub usingnamespace if (config.retain_metadata) struct {
            pub fn flushRetainedMetadata(self: *Self) void {
                self.freeRetainedMetadata();
                // also remove entries from large_allocations
                var it = self.large_allocations.iterator();
                while (it.next()) |large| {
                    if (large.value_ptr.freed) {
                        _ = self.large_allocations.remove(@ptrToInt(large.value_ptr.bytes.ptr));
                    }
                }
            }
        } else struct {};

        pub fn deinit(self: *Self) bool {
            const leaks = if (config.safety) self.detectLeaks() else false;
            if (config.retain_metadata) {
                self.freeRetainedMetadata();
            }
            self.large_allocations.deinit(self.backing_allocator);
            self.* = undefined;
            return leaks;
        }

        fn collectStackTrace(first_trace_addr: usize, addresses: *[stack_n]usize) void {
            if (stack_n == 0) return;
            mem.set(usize, addresses, 0);
            var stack_trace = StackTrace{
                .instruction_addresses = addresses,
                .index = 0,
            };
            std.debug.captureStackTrace(first_trace_addr, &stack_trace);
        }

        fn reportDoubleFree(ret_addr: usize, alloc_stack_trace: StackTrace, free_stack_trace: StackTrace) void {
            var addresses: [stack_n]usize = [1]usize{0} ** stack_n;
            var second_free_stack_trace = StackTrace{
                .instruction_addresses = &addresses,
                .index = 0,
            };
            std.debug.captureStackTrace(ret_addr, &second_free_stack_trace);
            log.err("Double free detected. Allocation: {s} First free: {s} Second free: {s}", .{
                alloc_stack_trace, free_stack_trace, second_free_stack_trace,
            });
        }

        fn allocSlot(self: *Self, size_class: usize, trace_addr: usize) Error![*]u8 {
            const bucket_index = math.log2(size_class);
            const first_bucket = self.buckets[bucket_index] orelse try self.createBucket(
                size_class,
                bucket_index,
            );
            var bucket = first_bucket;
            const slot_count = @divExact(page_size, size_class);
            while (bucket.alloc_cursor == slot_count) {
                const prev_bucket = bucket;
                bucket = prev_bucket.next;
                if (bucket == first_bucket) {
                    // make a new one
                    bucket = try self.createBucket(size_class, bucket_index);
                    bucket.prev = prev_bucket;
                    bucket.next = prev_bucket.next;
                    prev_bucket.next = bucket;
                    bucket.next.prev = bucket;
                }
            }
            // change the allocator's current bucket to be this one
            self.buckets[bucket_index] = bucket;

            const slot_index = bucket.alloc_cursor;
            bucket.alloc_cursor += 1;

            var used_bits_byte = bucket.usedBits(slot_index / 8);
            const used_bit_index: u3 = @intCast(u3, slot_index % 8); // TODO cast should be unnecessary
            used_bits_byte.* |= (@as(u8, 1) << used_bit_index);
            bucket.used_count += 1;
            bucket.captureStackTrace(trace_addr, size_class, slot_index, .alloc);
            return bucket.page + slot_index * size_class;
        }

        fn searchBucket(
            bucket_list: ?*BucketHeader,
            addr: usize,
        ) ?*BucketHeader {
            const first_bucket = bucket_list orelse return null;
            var bucket = first_bucket;
            while (true) {
                const in_bucket_range = (addr >= @ptrToInt(bucket.page) and
                    addr < @ptrToInt(bucket.page) + page_size);
                if (in_bucket_range) return bucket;
                bucket = bucket.prev;
                if (bucket == first_bucket) {
                    return null;
                }
            }
        }

        /// This function assumes the object is in the large object storage regardless
        /// of the parameters.
        fn resizeLarge(
            self: *Self,
            old_mem: []u8,
            old_align: u29,
            new_size: usize,
            len_align: u29,
            ret_addr: usize,
        ) ?usize {
            const entry = self.large_allocations.getEntry(@ptrToInt(old_mem.ptr)) orelse {
                if (config.safety) {
                    @panic("Invalid free");
                } else {
                    unreachable;
                }
            };

            if (config.retain_metadata and entry.value_ptr.freed) {
                if (config.safety) {
                    reportDoubleFree(ret_addr, entry.value_ptr.getStackTrace(.alloc), entry.value_ptr.getStackTrace(.free));
                    @panic("Unrecoverable double free");
                } else {
                    unreachable;
                }
            }

            if (config.safety and old_mem.len != entry.value_ptr.bytes.len) {
                var addresses: [stack_n]usize = [1]usize{0} ** stack_n;
                var free_stack_trace = StackTrace{
                    .instruction_addresses = &addresses,
                    .index = 0,
                };
                std.debug.captureStackTrace(ret_addr, &free_stack_trace);
                log.err("Allocation size {d} bytes does not match free size {d}. Allocation: {s} Free: {s}", .{
                    entry.value_ptr.bytes.len,
                    old_mem.len,
                    entry.value_ptr.getStackTrace(.alloc),
                    free_stack_trace,
                });
            }

            // Do memory limit accounting with requested sizes rather than what backing_allocator returns
            // because if we want to return error.OutOfMemory, we have to leave allocation untouched, and
            // that is impossible to guarantee after calling backing_allocator.rawResize.
            const prev_req_bytes = self.total_requested_bytes;
            if (config.enable_memory_limit) {
                const new_req_bytes = prev_req_bytes + new_size - entry.value_ptr.requested_size;
                if (new_req_bytes > prev_req_bytes and new_req_bytes > self.requested_memory_limit) {
                    return null;
                }
                self.total_requested_bytes = new_req_bytes;
            }

            const result_len = self.backing_allocator.rawResize(old_mem, old_align, new_size, len_align, ret_addr) orelse {
                if (config.enable_memory_limit) {
                    self.total_requested_bytes = prev_req_bytes;
                }
                return null;
            };

            if (config.enable_memory_limit) {
                entry.value_ptr.requested_size = new_size;
            }

            if (config.verbose_log) {
                log.info("large resize {d} bytes at {*} to {d}", .{
                    old_mem.len, old_mem.ptr, new_size,
                });
            }
            entry.value_ptr.bytes = old_mem.ptr[0..result_len];
            entry.value_ptr.captureStackTrace(ret_addr, .alloc);
            return result_len;
        }

        /// This function assumes the object is in the large object storage regardless
        /// of the parameters.
        fn freeLarge(
            self: *Self,
            old_mem: []u8,
            old_align: u29,
            ret_addr: usize,
        ) void {
            _ = old_align;

            const entry = self.large_allocations.getEntry(@ptrToInt(old_mem.ptr)) orelse {
                if (config.safety) {
                    @panic("Invalid free");
                } else {
                    unreachable;
                }
            };

            if (config.retain_metadata and entry.value_ptr.freed) {
                if (config.safety) {
                    reportDoubleFree(ret_addr, entry.value_ptr.getStackTrace(.alloc), entry.value_ptr.getStackTrace(.free));
                    return;
                } else {
                    unreachable;
                }
            }

            if (config.safety and old_mem.len != entry.value_ptr.bytes.len) {
                var addresses: [stack_n]usize = [1]usize{0} ** stack_n;
                var free_stack_trace = StackTrace{
                    .instruction_addresses = &addresses,
                    .index = 0,
                };
                std.debug.captureStackTrace(ret_addr, &free_stack_trace);
                log.err("Allocation size {d} bytes does not match free size {d}. Allocation: {s} Free: {s}", .{
                    entry.value_ptr.bytes.len,
                    old_mem.len,
                    entry.value_ptr.getStackTrace(.alloc),
                    free_stack_trace,
                });
            }

            if (!config.never_unmap) {
                self.backing_allocator.rawFree(old_mem, old_align, ret_addr);
            }

            if (config.enable_memory_limit) {
                self.total_requested_bytes -= entry.value_ptr.requested_size;
            }

            if (config.verbose_log) {
                log.info("large free {d} bytes at {*}", .{ old_mem.len, old_mem.ptr });
            }

            if (!config.retain_metadata) {
                assert(self.large_allocations.remove(@ptrToInt(old_mem.ptr)));
            } else {
                entry.value_ptr.freed = true;
                entry.value_ptr.captureStackTrace(ret_addr, .free);
            }
        }

        pub fn setRequestedMemoryLimit(self: *Self, limit: usize) void {
            self.requested_memory_limit = limit;
        }

        fn free(
            self: *Self,
            old_mem: []u8,
            old_align: u29,
            ret_addr: usize,
        ) void {
            self.mutex.lock();
            defer self.mutex.unlock();

            assert(old_mem.len != 0);

            const aligned_size = math.max(old_mem.len, old_align);
            if (aligned_size > largest_bucket_object_size) {
                self.freeLarge(old_mem, old_align, ret_addr);
                return;
            }
            const size_class_hint = math.ceilPowerOfTwoAssert(usize, aligned_size);

            var bucket_index = math.log2(size_class_hint);
            var size_class: usize = size_class_hint;
            const bucket = while (bucket_index < small_bucket_count) : (bucket_index += 1) {
                if (searchBucket(self.buckets[bucket_index], @ptrToInt(old_mem.ptr))) |bucket| {
                    // move bucket to head of list to optimize search for nearby allocations
                    self.buckets[bucket_index] = bucket;
                    break bucket;
                }
                size_class *= 2;
            } else blk: {
                if (config.retain_metadata) {
                    if (!self.large_allocations.contains(@ptrToInt(old_mem.ptr))) {
                        // object not in active buckets or a large allocation, so search empty buckets
                        if (searchBucket(self.empty_buckets, @ptrToInt(old_mem.ptr))) |bucket| {
                            // bucket is empty so is_used below will always be false and we exit there
                            break :blk bucket;
                        } else {
                            @panic("Invalid free");
                        }
                    }
                }
                self.freeLarge(old_mem, old_align, ret_addr);
                return;
            };
            const byte_offset = @ptrToInt(old_mem.ptr) - @ptrToInt(bucket.page);
            const slot_index = @intCast(SlotIndex, byte_offset / size_class);
            const used_byte_index = slot_index / 8;
            const used_bit_index = @intCast(u3, slot_index % 8);
            const used_byte = bucket.usedBits(used_byte_index);
            const is_used = @truncate(u1, used_byte.* >> used_bit_index) != 0;
            if (!is_used) {
                if (config.safety) {
                    reportDoubleFree(ret_addr, bucketStackTrace(bucket, size_class, slot_index, .alloc), bucketStackTrace(bucket, size_class, slot_index, .free));
                    // Recoverable if this is a free.
                    return;
                } else {
                    unreachable;
                }
            }

            // Definitely an in-use small alloc now.
            if (config.enable_memory_limit) {
                self.total_requested_bytes -= old_mem.len;
            }

            // Capture stack trace to be the "first free", in case a double free happens.
            bucket.captureStackTrace(ret_addr, size_class, slot_index, .free);

            used_byte.* &= ~(@as(u8, 1) << used_bit_index);
            bucket.used_count -= 1;
            if (bucket.used_count == 0) {
                if (bucket.next == bucket) {
                    // it's the only bucket and therefore the current one
                    self.buckets[bucket_index] = null;
                } else {
                    bucket.next.prev = bucket.prev;
                    bucket.prev.next = bucket.next;
                    self.buckets[bucket_index] = bucket.prev;
                }
                if (!config.never_unmap) {
                    self.backing_allocator.free(bucket.page[0..page_size]);
                }
                if (!config.retain_metadata) {
                    self.freeBucket(bucket, size_class);
                } else {
                    // move alloc_cursor to end so we can tell size_class later
                    const slot_count = @divExact(page_size, size_class);
                    bucket.alloc_cursor = @truncate(SlotIndex, slot_count);
                    if (self.empty_buckets) |prev_bucket| {
                        // empty_buckets is ordered newest to oldest through prev so that if
                        // config.never_unmap is false and backing_allocator reuses freed memory
                        // then searchBuckets will always return the newer, relevant bucket
                        bucket.prev = prev_bucket;
                        bucket.next = prev_bucket.next;
                        prev_bucket.next = bucket;
                        bucket.next.prev = bucket;
                    } else {
                        bucket.prev = bucket;
                        bucket.next = bucket;
                    }
                    self.empty_buckets = bucket;
                }
            } else {
                @memset(old_mem.ptr, undefined, old_mem.len);
            }
            if (config.verbose_log) {
                log.info("small free {d} bytes at {*}", .{ old_mem.len, old_mem.ptr });
            }
        }

        // Returns true if an allocation of `size` bytes is within the specified
        // limits if enable_memory_limit is true
        fn isAllocationAllowed(self: *Self, size: usize) bool {
            if (config.enable_memory_limit) {
                const new_req_bytes = self.total_requested_bytes + size;
                if (new_req_bytes > self.requested_memory_limit)
                    return false;
                self.total_requested_bytes = new_req_bytes;
            }

            return true;
        }

        fn alloc(self: *Self, len: usize, ptr_align: u29, len_align: u29, ret_addr: usize) Error![]u8 {
            self.mutex.lock();
            defer self.mutex.unlock();

            if (!self.isAllocationAllowed(len)) {
                return error.OutOfMemory;
            }

            const new_aligned_size = math.max(len, ptr_align);
            if (new_aligned_size > largest_bucket_object_size) {
                try self.large_allocations.ensureUnusedCapacity(self.backing_allocator, 1);
                const slice = try self.backing_allocator.rawAlloc(len, ptr_align, len_align, ret_addr);

                const gop = self.large_allocations.getOrPutAssumeCapacity(@ptrToInt(slice.ptr));
                if (config.retain_metadata and !config.never_unmap) {
                    // Backing allocator may be reusing memory that we're retaining metadata for
                    assert(!gop.found_existing or gop.value_ptr.freed);
                } else {
                    assert(!gop.found_existing); // This would mean the kernel double-mapped pages.
                }
                gop.value_ptr.bytes = slice;
                if (config.enable_memory_limit)
                    gop.value_ptr.requested_size = len;
                gop.value_ptr.captureStackTrace(ret_addr, .alloc);
                if (config.retain_metadata) {
                    gop.value_ptr.freed = false;
                    if (config.never_unmap) {
                        gop.value_ptr.ptr_align = ptr_align;
                    }
                }

                if (config.verbose_log) {
                    log.info("large alloc {d} bytes at {*}", .{ slice.len, slice.ptr });
                }
                return slice;
            }

            const new_size_class = math.ceilPowerOfTwoAssert(usize, new_aligned_size);
            const ptr = try self.allocSlot(new_size_class, ret_addr);
            if (config.verbose_log) {
                log.info("small alloc {d} bytes at {*}", .{ len, ptr });
            }
            return ptr[0..len];
        }

        fn createBucket(self: *Self, size_class: usize, bucket_index: usize) Error!*BucketHeader {
            const page = try self.backing_allocator.allocAdvanced(u8, page_size, page_size, .exact);
            errdefer self.backing_allocator.free(page);

            const bucket_size = bucketSize(size_class);
            const bucket_bytes = try self.backing_allocator.allocAdvanced(u8, @alignOf(BucketHeader), bucket_size, .exact);
            const ptr = @ptrCast(*BucketHeader, bucket_bytes.ptr);
            ptr.* = BucketHeader{
                .prev = ptr,
                .next = ptr,
                .page = page.ptr,
                .alloc_cursor = 0,
                .used_count = 0,
            };
            self.buckets[bucket_index] = ptr;
            // Set the used bits to all zeroes
            @memset(@as(*[1]u8, ptr.usedBits(0)), 0, usedBitsCount(size_class));
            return ptr;
        }
    };
}
