// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#include "utils.h"
#include "get_time.h"

#define NUM_STEPS	2000000
#define NUM_THREADS	10

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static int var;

static void *increase_var(void *arg)
{
	size_t i;

	(void)arg;

#ifdef FINE_GRAINED
	for (i = 0; i < NUM_STEPS; ++i) {
		pthread_mutex_lock(&lock);	/* Begin critical section. */
		++var;
		pthread_mutex_unlock(&lock);	/* End critical section. */
	}
#elif COARSE_GRAINED
	pthread_mutex_lock(&lock);		/* Begin critical section. */
	for (i = 0; i < NUM_STEPS; ++i)
		++var;
	pthread_mutex_unlock(&lock);		/* End critical section. */
#endif

	return  NULL;
}

int main(void)
{
	int rc;
	void *retval;
	size_t i;
	pthread_t tids[NUM_THREADS];
	unsigned long millis_start;
	unsigned long millis_end;

	millis_start = get_current_millis();

	for (i = 0; i < NUM_THREADS; ++i) {
		rc = pthread_create(tids + i, NULL, increase_var, NULL);
		DIE(rc < 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(tids[i], &retval);
		DIE(rc < 0, "pthread_create");
	}

	millis_end = get_current_millis();

	printf("var = %d; time = %lu ms\n", var, millis_end - millis_start);

	return 0;
}
