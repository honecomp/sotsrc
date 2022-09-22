#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>

enum {
	Maxline = 500,
};

void
printevent(char *e)
{
	time_t now;
	char *p;

	time(&now);
	p = ctime(&now);
	p[strlen(p) - 1] = '\0';
	printf("%s: %s", p, e);
}

int
main(int argc, char **argv)
{
	FILE *st;
	char line[Maxline];

	if (access("/tmp/logger", F_OK) == 0)
		if (unlink("/tmp/logger") < 0)
			err(EXIT_FAILURE, "cant remove /tmp/logger");

	if (mkfifo("/tmp/logger", 0664) < 0)
		err(EXIT_FAILURE, "cannot make fifo /tmp/logger");

	for (;;) {
		printevent("waiting for clients\n");
		st = fopen("/tmp/logger", "r");
		if (st == NULL) {
			errx(EXIT_FAILURE, "fopen error");
		}
		printevent("ready to read events\n");
		while (fgets(line, Maxline, st) != NULL) {
			printevent(line);
		}
		if (ferror(st)) {
			errx(EXIT_FAILURE, "read error");
		}
		printevent("client is gone\n");
		fclose(st);
	}
}
