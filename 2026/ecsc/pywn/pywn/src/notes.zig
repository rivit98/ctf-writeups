const std = @import("std");

const c = @cImport({
    @cInclude("stdio.h");
    @cInclude("stdlib.h");
    @cInclude("string.h");
});

const Note = extern struct {
    name: ?[*:0]u8,
    num_records: c_int,
    records: ?[*]c_int,
};

const allocator = std.heap.smp_allocator;

export fn note_create(
    name_length: c_int,
    name: [*:0]const u8,
    num_records: c_int,
) ?*Note {
    const note = allocator.create(Note) catch {
        return null;
    };
    errdefer allocator.destroy(note);

    const records = if (num_records > 0)
        (allocator.alloc(c_int, @intCast(num_records)) catch {
            return null;
        })
    else
        null;
    errdefer if (num_records > 0) allocator.free(records);

    const name_buf = allocator.alloc(u8, @intCast(name_length + 1)) catch {
        return null;
    };
    errdefer allocator.free(name_buf);

    _ = c.strcpy(name_buf.ptr, name);

    note.* = .{
        .name = @ptrCast(name_buf.ptr),
        .num_records = num_records,
        .records = @ptrCast(if (records) |rs| rs.ptr else null),
    };

    return note;
}

export fn note_delete(note: ?*Note) void {
    if (note == null) {
        return;
    }

    const n = note.?;

    if (n.name) |name| {
        allocator.free(std.mem.span(name));
        n.name = null;
    }

    if (n.records) |records| {
        allocator.free(records[0..@intCast(n.num_records)]);
        n.records = null;
    }

    n.num_records = 0;

    allocator.destroy(n);
}

export fn note_best_record(note: ?*Note) c_int {
    const n = note.?;
    var result: c_int = std.math.minInt(c_int);
    for (0..@intCast(n.num_records)) |i| {
        const r = n.records.?[i];
        if (r > result) {
            result = r;
        }
    }
    return result;
}

export fn note_worst_record(note: ?*Note) c_int {
    const n = note.?;
    var result: c_int = std.math.maxInt(c_int);
    for (0..@intCast(n.num_records)) |i| {
        const r = n.records.?[i];
        if (r < result) {
            result = r;
        }
    }
    return result;
}
