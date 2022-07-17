from pwn import *

elf = ELF("./suscall")
p = gdb.debug(elf.path, '\n'.join([
			"b *0x401F60", # main
			"c",
			"set context-sections regs",
			"set logging off",
			"set logging overwrite on",
			"set logging file ./gdb-trace.txt",
			"set logging redirect on",
			"set logging debugredirect on",
			"set logging on",
			"while(1) ",
			"ctx regs",
			"stepi",
			"end",
			"quit"
		]))

p.sendline(b'ecsc{asdasaaadasdasdasd}')
p.wait_for_close()
