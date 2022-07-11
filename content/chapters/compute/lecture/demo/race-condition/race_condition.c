// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#include "utils.h"
#include "get_time.h"

#define NUM_STEPS	1000000
#define NUM_THREADS	2

#ifdef ATOMIC
#include <stdatomic.h>
#elif USE_SPINLOCK
static pthread_spinlock_t lock;
#elif USE_MUTEX
static pthread_mutex_t lock;
#endif

static void acquire_lock(void)
{
	int rc;

	(void) rc;

#ifdef USE_SPINLOCK
	rc = pthread_spin_lock(&lock);
	DIE(rc, "pthread_spin_lock");
#elif USE_MUTEX
	rc = pthread_mutex_lock(&lock);
	DIE(rc, "pthread_mutex_lock");
#endif
}

static void release_lock(void)
{
	int rc;

	(void) rc;

#ifdef USE_SPINLOCK
	rc = pthread_spin_unlock(&lock);
	DIE(rc, "pthread_spin_unlock");
#elif USE_MUTEX
	rc = pthread_mutex_unlock(&lock);
	DIE(rc, "pthread_mutex_unlock");
#endif
}

static int var;

static void *increase_var(void *arg)
{
	size_t i;

	(void)arg;

	for (i = 0; i < NUM_STEPS; ++i) {
		acquire_lock();	/* Begin critical section. */
#ifdef ATOMIC
		atomic_fetch_add(&var, 1);
#else
		++var;
#endif
		release_lock();	/* End critical section. */
	}

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

#ifdef USE_SPINLOCK
	rc = pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
	DIE(rc, "pthread_spin_init");
#elif USE_MUTEX
	rc = pthread_mutex_init(&lock, NULL);
	DIE(rc, "pthread_mutex_init");
#endif

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

#ifdef USE_SPINLOCK
	rc = pthread_spin_destroy(&lock);
	DIE(rc, "pthread_spin_destroy");
#elif USE_MUTEX
	rc = pthread_mutex_destroy(&lock);
	DIE(rc, "pthread_mutex_destroy");
#endif

	printf("var = %d; time = %lu ms\n", var, millis_end - millis_start);

	return 0;
}
