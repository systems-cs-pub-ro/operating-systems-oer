NASM = nasm
CC = gcc
CFLAGS = -fno-PIC -fno-stack-protector
LDFLAGS = -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none

.PHONY: all clean

all: main

main: main.o syscall.o

main.o: main.c syscall.h

syscall.o: syscall.s
	$(NASM) -f elf64 -o $@ $<

clean:
	-rm -f main
	-rm -f main.o syscall.o
	-rm -f *~
