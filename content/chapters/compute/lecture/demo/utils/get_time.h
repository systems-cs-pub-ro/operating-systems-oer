/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef GET_TIME_H_
#define GET_TIME_H_ 1

#include <stdio.h>
#include <sys/time.h>

static unsigned long get_current_millis(void)
{
	struct timeval tv;
	int rc = gettimeofday(&tv, NULL);

	DIE(rc < 0, "gettimeofday");

	return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

#endif  /* GET_TIME_H_ */
