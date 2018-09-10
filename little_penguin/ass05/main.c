// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_LEN 8
static char receive[BUFFER_LEN];

int main(int ac, char **av)
{
	if (ac > 1) {
		int ret, fd;

		fd = open("/dev/fortytwo", O_RDWR);

		if (fd < 0) {
			perror("failed to open device");
			return errno;
		}
		ret = write(fd, av[1], strlen(av[1]));
		if (ret < 0) {
			perror("failed to write message to device");
			return errno;
		}
		close(fd);
		fd = open("/dev/fortytwo", O_RDWR);
		ret = read(fd, receive, BUFFER_LEN);
		if (ret < 0) {
			perror("failed to read message from device");
			return errno;
		}
		printf("%s", receive);
	} else {
		printf("Please add input\n");
		return 0;
	}
	return 0;
}
