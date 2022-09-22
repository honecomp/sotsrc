#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

enum {
	Bufsize = 8 * 1024,
};

int
main(int argc, char *argv[])
{
	char buf[Bufsize];
	int nr;

	while ((nr = read(0, buf, Bufsize)) != 0) {
		if (nr < 0) {
			err(EXIT_FAILURE, "can't read");
		}
		if (write(1, buf, nr) != nr) {
			err(EXIT_FAILURE, "can't write");
		}
	}
	exit(EXIT_SUCCESS);
}
