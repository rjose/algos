stack.o: stack.nasm
	nasm -f elf -g -F stabs $< -l stack.lst

stack: stack.o
	ld -o $@ $<
