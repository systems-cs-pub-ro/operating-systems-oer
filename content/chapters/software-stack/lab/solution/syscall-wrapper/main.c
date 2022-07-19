#include "syscall.h"

static void reverse_string(char *a, unsigned int len)
{
	unsigned int i, j;
	char aux;

	for (i = 0, j = len-1; i < j; i++, j--) {
		aux = a[i];
		a[i] = a[j];
		a[j] = aux;
	}
}
	
static unsigned int itoa(int n, char *a)
{
	unsigned int num_digits = 0;
	int digit;

	while (1) {
		digit = n % 10;
		a[num_digits] = '0' + digit;
		num_digits++;

		n = n / 10;
		if (n == 0)
			break;
	}

	reverse_string(a, num_digits);

	/* Add a NUL-terminator at end of string. */
	a[num_digits] = '\0';

	return num_digits;
}

int main(void)
{
	char buffer[128];
	int n;
	int pid;
	unsigned int num_digits;

	write(1, "Hello, world!\n", 14);

	/* Read and write back input from standard input. */
	write(1, "Give input: ", 12);
	n = read(0, buffer, 128);
	write(1, "Here's your input back: ", 24);
	write(1, buffer, n);

	/* Get and print the process ID. */
	pid = getpid();
	num_digits = itoa(pid, buffer);
	write(1, "PID: ", 5);
	write(1, buffer, num_digits);
	write(1, "\n", 1);

	exit(0);
	return 0;
}
