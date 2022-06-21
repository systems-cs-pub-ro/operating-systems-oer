#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <openssl/sha.h>

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

void worker(int idx, int request_pipe_fd, int result_pipe_fd)
{
	char first_char;
	int ret;
	char password[PASSWORD_LEN+1];
	int i, k;
	int found = 0;
	int v;

	/*
	 * read the first character of the password
	 */

	ret = read(request_pipe_fd, &first_char, sizeof(first_char));
	if (ret <= 0) {
		perror("read");
		return;
	}

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
		/*
		 * found the password. send the password length and the password
		 * through the pipe
		 */
		v = PASSWORD_LEN;

		ret = write(result_pipe_fd, &v, sizeof(v));
		if (ret < 0) {
			perror("write");
			exit(1);
		}

		ret = write(result_pipe_fd, password, PASSWORD_LEN);
		if (ret < 0) {
			perror("write");
			exit(1);
		}
	} else {
		/*
		 * didn't find the password. send the value 0 through the pipe
		 */
		v = 0;

		ret = write(result_pipe_fd, &v, sizeof(v));
		if (ret < 0) {
			perror("write");
			exit(1);
		}
	}
}

void create_workers(int *request_pipefd, int *result_pipefd)
{
	int tmp_request_pipe[2];
	int tmp_result_pipe[2];
	int ret;
	int pid;
	int i;

	for (i = 0; i < NUM_WORKERS; i++) {
		ret = pipe(tmp_request_pipe);
		if (ret < 0) {
			perror("pipe");
			exit(1);
		}

		ret = pipe(tmp_result_pipe);
		if (ret < 0) {
			perror("pipe");
			exit(1);
		}

		pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(1);
		}

		if (pid == 0) {
			close(tmp_request_pipe[1]);
			close(tmp_result_pipe[0]);

			worker(i, tmp_request_pipe[0], tmp_result_pipe[1]);
			exit(0);
		}

		close(tmp_request_pipe[0]);
		close(tmp_result_pipe[1]);

		request_pipefd[i] = tmp_request_pipe[1];
		result_pipefd[i] = tmp_result_pipe[0];
	}
}

int main()
{
	int i;
	int request_pipefd[NUM_WORKERS];
	int result_pipefd[NUM_WORKERS];
	int len;
	int ret;
	char char_list[] = "abcdefghijklmnopqrstuvwxyz";
	char password[PASSWORD_LEN+1];

	create_workers(request_pipefd, result_pipefd);

	printf("Worker processes started. Press ENTER\n");
	getchar();

	for (i = 0; i < NUM_WORKERS; i++) {
		ret = write(request_pipefd[i], &char_list[i], sizeof(char));
		if (ret < 0) {
			perror("write");
			return 1;
		}
	}

	for (i = 0; i < NUM_WORKERS; i++) {
		ret = read(result_pipefd[i], &len, sizeof(len));
		if (ret < 0) {
			perror("read");
			return 1;
		}

		if (len) {
			ret = read(result_pipefd[i], password, len);
			if (ret < 0) {
				perror("read");
				return 1;
			}

			password[len] = 0;

			printf("worker %d found %s\n", i, password);
		} else {
			printf("worker %d did't find anything\n", i);
		}
	}

	for (i = 0; i < NUM_WORKERS; i++) {
		ret = wait(NULL);
		if (ret < 0) {
			perror("wait");
			return 1;
		}
	}

	return 0;
}
