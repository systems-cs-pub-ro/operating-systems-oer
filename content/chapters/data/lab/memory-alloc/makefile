DMD=gdc
DFLAGS=

CC=gcc
CFLAGS=

c_memory_alloc: c_memory_alloc.c
	$(CC) $(CFLAGS) -o $@ $?

d_memory_alloc: d_memory_alloc.d
	$(DMD) $(DFLAGS) -o $@ $?

clean:
	rm -rf c_memory_alloc d_memory_alloc
