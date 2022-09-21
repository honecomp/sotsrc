#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/file.h>

enum {
	Nprocs = 10,
	Maxstr = 256,
	Nrounds = 5,
};

void
dowrite(int fd)
{
	char str[Maxstr];
	int i;

	for (i = 0; i < Nrounds; i++) {
		snprintf(str, Maxstr, "PID %d was here! round %d\n",
			 getpid(), i);
		if (write(fd, str, strlen(str)) != strlen(str))
			err(EXIT_FAILURE, "can't write file");
	}
}

void
child(char *path)
{
	int fd;

	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		err(EXIT_FAILURE, "can't create file %s", path);
	dowrite(fd);
	close(fd);
}

int
main(int argc, char *argv[])
{
	int i;

	if (argc != 2)
		errx(EXIT_FAILURE, "usage: %s file", argv[0]);

	unlink(argv[1]);

	for (i = 0; i < Nprocs; i++) {
		switch (fork()) {
		case -1:
			err(EXIT_FAILURE, "can't fork");
		case 0:
			child(argv[1]);
			exit(EXIT_SUCCESS);
		}
	}
	while (wait(NULL) != -1)
		fprintf(stderr, ".");
	fprintf(stderr, "\n");
	exit(EXIT_SUCCESS);
}
