// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#include "utils.h"

void *thread_func(void *arg)
{
	char *msg = arg;

	printf("[thread] PID = %d; PPID = %d\n", getpid(), getppid());
	printf("[thread] Message from main thread: %s\n", msg);

	sleep(5);

	return NULL;
}

int main(void)
{
	pthread_t tid;
	int rc;
	char *msg = "SO Rullz!";

	printf("[main] PID = %d; PPID = %d\n", getpid(), getppid());

	/* Create and start a new thread. */
	rc = pthread_create(&tid, NULL, thread_func, msg);
	DIE(rc, "pthread_create");

	rc = pthread_join(tid, NULL);
	DIE(rc, "pthread_join");

	return 0;
}
