DMD=gdc
DFLAGS=

CC=gcc
CFLAGS= -Wall

all: c_sefault d_segfault

c_sefault: segfault.c
	$(CC) $(CFLAGS) -o $@ $?

d_segfault: segfault.d
	$(DMD) $(DFLAGS) -o $@ $?

clean:
	rm -rf c_sefault d_segfault
