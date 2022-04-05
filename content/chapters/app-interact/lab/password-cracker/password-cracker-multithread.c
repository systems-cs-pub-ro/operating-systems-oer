#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <openssl/sha.h>
#include <pthread.h>

#define NUM_WORKERS 26

#define PASSWORD_LEN 4

#define PASSWORD_HASH "\x59\xa5\xab\xc2\xa9\x9b\x95\xbe"		\
	"\x73\xc3\x1e\xa2\x72\xab\x0f\x2f"				\
	"\x2f\xe4\x2f\xec\x30\x36\x71\x55"				\
	"\xcb\x73\xf6\xf6\xce\xf1\xf4\xe6"				\
	"\xee\x37\xf5\x86\xcb\xd0\x2c\xc7"				\
	"\x38\xa8\x7a\x5d\x6a\xdd\x3b\xa3"				\
	"\x1d\xbe\xaf\x39\xec\x77\xca\xd9"				\
	"\x10\x83\x7c\x94\xc6\x58\x37\xfb"
#define HASH_LEN 64

int check_password(char *password, int len)
{
	unsigned char hash[HASH_LEN];

	SHA512((unsigned char *)password, len, hash);

	return memcmp(hash, PASSWORD_HASH, HASH_LEN) == 0;
}

void *worker(void *arg)
{
	char first_char;
	char password[PASSWORD_LEN+1];
	int i, k;
	int found = 0;

	first_char = (char)arg;

	password[0] = first_char;

	for (i = 1; i < PASSWORD_LEN; i++)
		password[i] = -1;

	/*
	 * generate all possible combinations
	 */
	k = 1;

	while (k >= 1) {
		if (password[k] < 'z') {
			password[k]++;

			if (k < PASSWORD_LEN) {
				k++;
				password[k] = '`';
			}
		}

		if (k == PASSWORD_LEN) {
			/* check one combination */
			if (check_password(password, PASSWORD_LEN)) {
				found = 1;
				break;
			}
		}

		if ((password[k] == 'z') || (k == PASSWORD_LEN)) {
			k--;
		}
	}

	if (found) {
		char *p;

		password[PASSWORD_LEN] = 0;
		p = strdup(password);

		return p;
	} else {
		return NULL;
	}
}

void create_workers(pthread_t *tids)
{
	int ret;
	int i;
	char char_list[] = "abcdefghijklmnopqrstuvwxyz";

	for (i = 0; i < NUM_WORKERS; i++) {
		ret = pthread_create(&tids[i], NULL, worker, (void *)char_list[i]);
		if (ret) {
			perror("pthread_create");
			exit(1);
		}
	}
}

int main()
{
	pthread_t tids[NUM_WORKERS];
	int i;
	int ret;
	char *password;

	create_workers(tids);

	for (i = 0; i < NUM_WORKERS; i++) {
		ret = pthread_join(tids[i], (void **)&password);
		if (ret < 0) {
			perror("pthread_join");
			return 1;
		}

		if (password) {
			printf("worker %d found %s\n", i, password);
		} else {
			printf("worker %d did't find anything\n", i);
		}
	}

	return 0;
}
