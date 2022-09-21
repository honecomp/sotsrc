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

enum {
	Linelen = 256,
};

int
main(int argc, char *argv[])
{
	char line[Linelen];
	int fd[2];
	int i;
	int status;
	int lines;

	if (argc != 2) {
		errx(EXIT_FAILURE, "number of lines not found");
	}
	lines = atoi(argv[1]);
	if (lines <= 0) {
		errx(EXIT_FAILURE, "invalid number");
	}
	if (pipe(fd) < 0)
		err(EXIT_FAILURE, "cannot make a pipe");
	switch (fork()) {
	case -1:
		err(EXIT_FAILURE, "cannot fork");
	case 0:
		close(fd[1]);
		if (dup2(fd[0], 0) < 0) {
			err(EXIT_FAILURE, "dup failed");
		}
		close(fd[0]);
		execl("/usr/bin/wc", "wc", "-l", NULL);
		err(EXIT_FAILURE, "exec failed");
	}
	close(fd[0]);
	for (i = 0; i < lines; i++) {
		snprintf(line, Linelen, "This is the line %d\n", i);
		if (write(fd[1], line, strlen(line)) != strlen(line)) {
			err(EXIT_FAILURE, "write failed");
		}
	}
	close(fd[1]);
	if (wait(&status) < 0) {
		status = EXIT_FAILURE;
	}
	exit(WEXITSTATUS(status));
}
