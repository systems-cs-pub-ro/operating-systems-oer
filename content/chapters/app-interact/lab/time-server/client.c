#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#define MAX_SIZE 8

int connect_to_server(char *ip, char *port_str)
{
	int sockfd;
	int ret;
	struct sockaddr_in addr;
	short port;
	char *pend;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0) {
		perror("socket");
		return sockfd;
	}

	addr.sin_family = AF_INET;

	ret = inet_aton(ip, &addr.sin_addr);
	if (!ret) {
		fprintf(stderr, "Invalid ip: %s\n", ip);
		return ret;
	}

	port = strtoul(port_str, &pend, 10);
	if (!*port_str || *pend) {
		fprintf(stderr, "Invalid port: %s\n", port_str);
		return -1;
	}

	addr.sin_port = htons(port);

	ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0) {
		perror("connect");
		return ret;
	}

	return sockfd;
}

int xrecv(int sockfd, void *buf, size_t len, int flags)
{
	int ret;
	size_t i = 0;
	char *p = (char *)buf;

	while (i < len) {
		ret = recv(sockfd, &p[i], len-i, flags);
		if (ret < 0)
			return ret;

		if (ret == 0)
			break;

		i += ret;
	}

	return i;
}

int main(int argc, char *argv[])
{
	int sockfd;
	int ret;

	uint32_t size;
	time_t current_time;

	if (argc != 3) {
		fprintf(stderr, "Usage: client ip port\n");
		return 1;
	}

	sockfd = connect_to_server(argv[1], argv[2]);
	if (sockfd < 0) {
		fprintf(stderr, "Failed to create socket\n");
		return 1;
	}

	ret = xrecv(sockfd, &size, sizeof(size), 0);
	if (ret < 0) {
		perror("recv");
		return 1;
	}
	if (ret != sizeof(size)) {
		fprintf(stderr, "EOF\n");
		return 1;
	}

	if (size > MAX_SIZE) {
		fprintf(stderr, "Invalid size %u\n", size);
		return 1;
	}

	ret = xrecv(sockfd, &current_time, size, 0);
	if (ret < 0) {
		perror("recv");
		return 1;
	}
	if (ret != size) {
		fprintf(stderr, "EOF\n");
		return 1;
	}

	printf("The time is %s", ctime(&current_time));

	close(sockfd);

	return 0;
}
