cl = clang-15
flags = --target=riscv32 -march=rv32g -mabi=ilp32d -mno-relax

lab1b.s : lab1b.c
	$(cl) $(flags) lab1b.c -S -o lab1b.s

lab1b.o : lab1b.s
	$(cl) $(flags) lab1b.s -c -o lab1b.o

lab1b.x : lab1b.o
	ld.lld lab1b.o -o lab1b.x