CC = gcc
CFLAGS = -Wall

all: password-cracker-multiprocess password-cracker-multithread

password-cracker-multiprocess: password-cracker-multiprocess.c
	$(CC) $(CFLAGS) -o $@ $< -lcrypto

password-cracker-multithread: password-cracker-multithread.c
	$(CC) $(CFLAGS) -o $@ $< -lcrypto -lpthread

clean:
	rm -f password-cracker-multiprocess 	password-cracker-multithread
