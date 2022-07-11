/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef UTILS_H_
#define UTILS_H_ 1

#include <stdio.h>
#include <stdlib.h>

#if defined(__linux__) || defined(__Unikraft__)
#define DIE(assertion, call_description)			\
	do {							\
		if (assertion) {				\
			fprintf(stderr, "(%s, %d): ",		\
					__FILE__, __LINE__);	\
			perror(call_description);		\
			exit(EXIT_FAILURE);			\
		}						\
	} while (0)

#elif defined(_WIN32)
#include <Windows.h>

#define DIE(assertion, call_description)					\
	do {									\
		if (assertion) {						\
			fprintf(stderr, "(%s, %s, %d): ",			\
					__FILE__, __FUNCTION__, __LINE__);	\
			PrintLastError(call_description);			\
			exit(EXIT_FAILURE);					\
		}								\
	} while (0)

static VOID PrintLastError(const PCHAR message)
{
	CHAR errBuff[1024];

	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
		NULL,
		GetLastError(),
		0,
		errBuff,
		sizeof(errBuff) - 1,
		NULL);

	fprintf(stderr, "%s: %s\n", message, errBuff);
}
#endif
#endif  /* UTILS_H_ */
