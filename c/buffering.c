#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
nobuffering(int fd)
{
	int nr;
	char c;
	int count = 0;

	/*
	 * Wrong and slow. Just an example.
	 */
	while ((nr = read(fd, &c, 1)) != 0) {
		if (nr < 0) {
			err(EXIT_FAILURE, "cant read");
		}
		count++;
	}
	return count;
}

int
buffering(int fd)
{
	char c;
	int count = 0;
	FILE *f;

	f = fdopen(fd, "r");
	if (f == NULL) {
		err(EXIT_FAILURE, "cant fopen fd");
	}
	while (fread(&c, 1, 1, f) != 0) {
		count++;
	}
	if (!feof(f)) {
		errx(EXIT_FAILURE, "fread failed");
	}
	fclose(f);
	return count;
}

int
invalidflag(char *s)
{
	return strcmp(s, "-b") != 0 && strcmp(s, "-n") != 0;
}

int
main(int argc, char *argv[])
{
	int fd;
	int n;

	if (argc != 3 || invalidflag(argv[1]))
		errx(EXIT_FAILURE, "usage: %s [-b | -n] file", argv[0]);
	fd = open(argv[2], O_RDONLY);
	if (fd < 0) {
		err(EXIT_FAILURE, "cannot open file");
	}
	if (strcmp(argv[1], "-b") == 0) {
		n = buffering(fd);
	} else {
		n = nobuffering(fd);
	}
	printf("total: %d chars\n", n);
	close(fd);
	exit(EXIT_SUCCESS);
}
