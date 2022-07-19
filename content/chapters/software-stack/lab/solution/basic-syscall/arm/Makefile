CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
LDFLAGS = -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none

.PHONY: all clean

all: hello

hello: hello.o

hello.o: hello.s

clean:
	-rm -f hello.o hello
	-rm -f *~
