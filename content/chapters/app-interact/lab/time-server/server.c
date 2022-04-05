#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#define BIND_ADDR "0.0.0.0"
#define PORT 2000

int create_socket(char *addr, short port)
{
	int sockfd;
	struct sockaddr_in srv_addr;
	int ret;
	int val;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0) {
		perror("socket");
		return sockfd;
	}

	val = 1;

	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (ret < 0) {
		perror("setsockopt");
		return ret;
	}

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	ret = inet_aton(addr, &srv_addr.sin_addr);
	if (!ret) {
		fprintf(stderr, "Invalid IP address: %s\n", addr);
		return -1;
	}

	ret = bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret < 0) {
		perror("bind");
		return ret;
	}

	ret = listen(sockfd, 10);
	if (ret < 0) {
		perror("listen");
		return ret;
	}

	return sockfd;
}

int xsend(int sockfd, const void *buf, size_t len, int flags)
{
	int ret;
	size_t i = 0;
	const char *p = (const char *)buf;

	while (i < len) {
		ret = send(sockfd, &p[i], len-i, flags);
		if (ret < 0)
			return ret;

		if (ret == 0)
			break;

		i += ret;
	}

	return i;
}

int handle_client(int sockfd)
{
	int ret;
	time_t current_time;
	uint32_t size;

	current_time = time(NULL);

	size = sizeof(current_time);

	ret = xsend(sockfd, &size, sizeof(size), 0);
	if (ret < 0) {
		perror("send");
		return 0;
	}

	ret = xsend(sockfd, &current_time, size, 0);
	if (ret < 0) {
		perror("send");
		return 0;
	}

	return 1;
}

int main()
{
	int sockfd;

	sockfd = create_socket(BIND_ADDR, PORT);
	if (sockfd < 0) {
		fprintf(stderr, "Failed to create socket\n");
		return 1;
	}

	while (1) {
		struct sockaddr_in cl_addr;
		int cl_sockfd;
		socklen_t addr_len = sizeof(cl_addr);

		cl_sockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &addr_len);
		if (cl_sockfd < 0) {
			perror("accept");
			continue;
		}

		printf("Got connection from %s:%d\n", inet_ntoa(cl_addr.sin_addr), ntohs(cl_addr.sin_port));

		handle_client(cl_sockfd);

		close(cl_sockfd);
	}

	return 0;
}
