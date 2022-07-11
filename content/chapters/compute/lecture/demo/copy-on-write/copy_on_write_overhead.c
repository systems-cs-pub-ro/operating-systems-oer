// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include "utils.h"
#include "get_time.h"

#define NPAGES		(128 * 1024)

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Press ENTER to continue ...");
	fflush(stdout);
	fgets(buf, 32, stdin);
}

int main(void)
{
	pid_t pid;
	int rc;
	size_t i;
	char c;
	unsigned long millis_start;
	unsigned long millis_end;
	int page_size = getpagesize();
	char *mem = malloc(NPAGES * page_size);

	DIE(!mem, "malloc");

	/* Demand all pages. */
	for (i = 0; i < NPAGES; ++i)
		mem[i * page_size] = 'a';

	pid = fork();
	switch (pid) {
	case -1:	/* Error */
		DIE(1, "fork");
		break;

	case 0:		/* Child process */
		wait_for_input("Child process started");

		/* Measure the time spent reading. No COW. */
		millis_start = get_current_millis();

		for (i = 0; i < NPAGES; ++i)
			c = mem[i * page_size];

		millis_end = get_current_millis();

		printf("Time for reading %d pages: %lu ms\n", NPAGES,
			millis_end - millis_start);

		wait_for_input("Child process read pages");

		/* Measure the time spent writing. COW is performed. */
		millis_start = get_current_millis();

		for (i = 0; i < NPAGES; ++i)
			mem[i * page_size] = c + 1;

		millis_end = get_current_millis();

		printf("Time for writing to %d pages: %lu ms\n", NPAGES,
			millis_end - millis_start);

		wait_for_input("Child process wrote pages");

		exit(EXIT_SUCCESS);

	default:	/* Parent process */
		rc = waitpid(pid, NULL, 0);
		DIE(rc < 0, "waitpid");
		break;
	}

	wait_for_input("Parent process ending");

	return 0;
}
