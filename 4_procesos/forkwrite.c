#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int
main(int argc, char *argv[])
{
	int fd;

	switch (fork()) {
	case -1:
		err(EXIT_FAILURE, "can't fork");
	case 0:
		fd = open("/tmp/a", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (write(fd, "son\n", 4) != 4) {
			err(EXIT_FAILURE, "can't write");
		}
		break;
	default:
		fd = open("/tmp/a", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (write(fd, "father\n", 7) != 7) {
			err(EXIT_FAILURE, "can't write");
		}
	}
	close(fd);
	exit(EXIT_SUCCESS);
}
