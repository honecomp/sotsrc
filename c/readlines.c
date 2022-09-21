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
	Maxline = 256,
};

int
main(int argc, char *argv[])
{
	char line[Maxline];

	while (fgets(line, Maxline, stdin) != NULL) {
		printf("line: %s\n", line);
	}
	if (!feof(stdin)) {
		errx(EXIT_FAILURE, "eof not reached");
	}
	exit(EXIT_SUCCESS);
}
