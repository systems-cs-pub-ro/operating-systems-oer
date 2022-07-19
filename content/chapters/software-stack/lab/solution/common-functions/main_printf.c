#include "syscall.h"
#include "string.h"
#include "printf.h"

static const char src[] = "warhammer40k";
static char dest[128];
static char out_buffer[256];

static char putchar_buffer[1024];
static char putchar_buffer_len = 0;

void flush(void)
{
	write(1, putchar_buffer, putchar_buffer_len);
	putchar_buffer_len = 0;
}

/* _putchar implementation has to be provided. */
void _putchar(char character)
{
	putchar_buffer[putchar_buffer_len] = character;
	putchar_buffer_len++;
	if (character == '\n' || putchar_buffer_len == 1024)
		flush();
}

int main(void)
{
	printf("[before] src is at %p, len is %lu, content: \"%s\"\n", src, strlen(src), src);
	printf("[before] dest is at %p, len is %lu, content: \"%s\"\n", dest, strlen(dest), dest);

	printf("copying src to dest\n");
	strcpy(dest, src);

	printf("[after] src is at %p, len is %lu, content: \"%s\"\n", src, strlen(src), src);
	printf("[after] dest is at %p, len is %lu, content: \"%s\"\n", dest, strlen(dest), dest);

	printf("a");
	printf("b");
	flush();
	printf("c\n");

	exit(0);
	return 0;
}
