DMD=gdc
DFLAGS=

CC=gcc
CFLAGS=

c_memory_vuln: c_memory_vuln.c
	$(CC) $(CFLAGS) -o $@ $?

d_memory_vuln: d_memory_vuln.d
	$(DMD) $(DFLAGS) -o $@ $?

clean:
	rm -rf c_memory_vuln d_memory_vuln
