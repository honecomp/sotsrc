#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum {
	Bsize = 1024,
};

void
child(int *fd)
{
	char buf[Bsize];
	long n;

	close(fd[1]);
	n = read(fd[0], buf, Bsize);	//ojo, falta un bucle, mal escrito
	if (n < 0)
		err(EXIT_FAILURE, "cannot read from pipe");
	if (n > 0) {
		buf[n] = '\0';
		printf("Child: %s\n", buf);
	}
	close(fd[0]);
}

int
main(int argc, char *argv[])
{
	int fd[2];
	char *str = "I am your father";

	if (pipe(fd) < 0) {
		err(EXIT_FAILURE, "cannot make a pipe");
	}
	switch (fork()) {
	case -1:
		err(EXIT_FAILURE, "cannot fork");
	case 0:
		child(fd);
		exit(EXIT_SUCCESS);
	default:
		close(fd[0]);
		if (write(fd[1], str, strlen(str)) != strlen(str)) {
			err(EXIT_FAILURE, "error writting in pipe");
		}
		close(fd[1]);
	}
	exit(EXIT_SUCCESS);
}
