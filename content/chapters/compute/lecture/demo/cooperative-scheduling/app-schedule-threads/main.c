#include <stdio.h>

/* Import user configuration: */
#ifdef __Unikraft__
#include <uk/config.h>
#endif  /* __Unikraft__ */

#include <uk/sched.h>
#include <uk/schedcoop.h>

#include "../../utils/utils.h"

#define NUM_THREADS	2
#define NUM_STEPS	4

struct uk_sched *sched;

static void thread_func(void *arg)
{
	int i;
	int tid = *(int*)arg;

	printf("Thread %d created!\n", tid);

	for (i = 0; i < NUM_STEPS; i++) {
		printf("Thread %d: step %d\n", tid, i);

#ifdef CONFIG_APPSCHEDULETHREADS_COOPERATE
		uk_sched_yield();
#endif
	}

	printf("Thread %d finished!\n", tid);

#ifndef CONFIG_APPSCHEDULETHREADS_COOPERATE
		uk_sched_yield();
#endif
}

int main(void)
{
	struct uk_thread *threads[NUM_THREADS];
	int tids[NUM_THREADS];
	int i;
	int rc;
	
	/* The default scheduler is cooperative. */
	sched = uk_sched_get_default();
	DIE(!sched, "uk_sched_get_default");

	/* Create the two threads: */
	for (i = 0; i < NUM_THREADS; ++i) {
		tids[i] = i + 1;

		threads[i] = uk_thread_create("Thread 1", thread_func, tids + i);
		DIE(!threads[i], "uk_sched_get_default");
	}

	/* Wait for the threads to finish. */
	for (i = 0; i < NUM_THREADS; ++i) {
		rc = uk_thread_wait(threads[i]);
		DIE(rc, "uk_thread_wait");
	}

	return 0;
}
