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
isfileordir(struct stat *st)
{
	int isf;

	isf = (st->st_mode & S_IFMT) == S_IFREG;
	return isf || (st->st_mode & S_IFMT) == S_IFDIR;
}

int
main(int argc, char *argv[])
{
	struct stat st;
	unsigned int perms;

	if (argc != 2) {
		errx(EXIT_FAILURE, "usage:  %s file", argv[0]);
	}
	if (stat(argv[1], &st) < 0) {
		err(EXIT_FAILURE, "stat failed");
	}
	perms = ((unsigned long)st.st_mode) & 0777;
	if (isfileordir(&st)) {
		printf("size: %ld\nowner: %d\nperms: 0%o\n",
		       st.st_size, st.st_uid, perms);
	} else {
		errx(EXIT_FAILURE,
		     "%s is not a regular" "file or a directory", argv[1]);
	}
	exit(EXIT_SUCCESS);
}
