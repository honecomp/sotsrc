#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>

int
main(int argc, char *argv[])
{
	int fd;

	if (argc != 2) {
		errx(1, "usage: %s file", argv[0]);
	}
	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0640);
	if (fd < 0) {
		err(1, "can't open file");
	}
	dup2(fd, 1);
	close(fd);
	printf("hey hey hey!!!\n");
	exit(EXIT_SUCCESS);
}
