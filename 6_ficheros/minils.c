#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
	DIR *d;
	struct dirent *ent;

	if (argc != 2) {
		errx(EXIT_FAILURE, " usage: %s dir", argv[0]);
	}
	d = opendir(argv[1]);
	if (d == NULL) {
		err(EXIT_FAILURE, "opendir failed: %s", argv[1]);
	}
	while ((ent = readdir(d)) != NULL) {
		if (ent->d_name[0] != '.') {
			printf("%s\n", ent->d_name);
		}
	}
	closedir(d);
	exit(EXIT_SUCCESS);
}
