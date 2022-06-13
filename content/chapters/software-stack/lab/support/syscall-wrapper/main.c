#include "syscall.h"

int main(void)
{
	write(1, "Hello, world!\n", 14);
	exit(0);
	return 0;
}
