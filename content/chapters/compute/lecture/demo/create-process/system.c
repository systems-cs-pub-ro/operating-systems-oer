// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

extern char **environ;

int main(void)
{
	int rc;

	/* Spawn a new process that runs `ls -a`. */
	rc = system("ls -la");
	DIE(rc, "system");

	return 0;
}
