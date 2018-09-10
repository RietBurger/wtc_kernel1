// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_LEN 4096
static char receive[BUFFER_LEN];

int main(void)
{
	char stringtosend[BUFFER_LEN];
	int ret, fd;

	fd = open("/dev/reverse", O_RDWR);

	if (fd < 0) {
		perror("failed to open device");
		return errno;
	}
	printf("type a string\n");
	scanf("%[^\n]%*c", stringtosend);
	printf("writing message [%s]\n", stringtosend);

	ret = write(fd, stringtosend, strlen(stringtosend));
	if (ret < 0) {
		perror("failed to write message to device");
		return errno;
	}
	close(fd);
	fd = open("/dev/reverse", O_RDWR);
	ret = read(fd, receive, BUFFER_LEN);
	if (ret < 0) {
		perror("failed to read message from device");
		return errno;
	}
	printf("Message received: %s\n", receive);
	return 0;
}
