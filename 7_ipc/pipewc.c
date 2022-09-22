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

int
main(int argc, char *argv[])
{
	int fd[2];
	char *str = "I am your father\n";
	int status;

	if (pipe(fd) < 0) {
		err(EXIT_FAILURE, "cannot make a pipe");
	}
	switch (fork()) {
	case -1:
		err(EXIT_FAILURE, "fork failed");
	case 0:
		close(fd[1]);
		if (dup2(fd[0], 0) < 0) {
			err(EXIT_FAILURE, "dup failed");
		}
		close(fd[0]);
		execl("/usr/bin/wc", "wc", "-w", NULL);
		err(EXIT_FAILURE, "exec failed");
	default:
		close(fd[0]);
		if (write(fd[1], str, strlen(str)) != strlen(str)) {
			err(EXIT_FAILURE, "error writting in pipe");
		}
		close(fd[1]);
		if (wait(&status) < 0) {
			status = EXIT_FAILURE;
		}
	}
	exit(status);
}
