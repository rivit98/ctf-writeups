payload: FORCE
	nasm -f elf64 -o payload.o payload.asm
	ld -o payload payload.o 
	python3 ./prepare.py payload
	rm -f /workspace/sandboxed
	pkill sandboxed

prctl: FORCE
	nasm -f elf64 -o prctl.o prctl.asm
	ld -o prctl prctl.o 
	python3 ./prepare.py prctl
	rm -f /workspace/sandboxed
	pkill sandboxed


FORCE: ;
