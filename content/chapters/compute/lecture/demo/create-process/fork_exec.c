// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "utils.h"

int main(void)
{
	pid_t pid;
	int rc;
	int exit_code;

	pid = fork();
	switch (pid) {
	case -1:	/* Error */
		DIE(1, "fork");
		break;

	case 0:		/* Child process */
		printf("[child] PID = %d; PPID = %d\n", getpid(), getppid());
		printf("[child] Executing `ls -la`...\n");

		rc = execlp("ls", "-la", NULL);
		DIE(rc, "execlp");
		break;

	default:	/* Parent process */
		printf("[parent] PID = %d; child PID = %d; Waiting...\n",
			getpid(), pid);

		rc = waitpid(pid, &exit_code, 0);
		DIE(rc < 0, "waitpid");

		printf("[parent] Child exited with code %d\n", exit_code);
		break;
	}

	return 0;
}
