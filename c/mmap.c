#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <err.h>
#include <ctype.h>

int
main(int argc, char *argv[])
{
	int fd;
	void *fmem;
	char *array;
	struct stat st;
	int i;

	if (argc != 2)
		errx(EXIT_FAILURE, "usage: %s file", argv[0]);
	fd = open(argv[1], O_RDWR);
	if (fd < 0)
		err(EXIT_FAILURE, "can't open file");
	if (fstat(fd, &st) < 0)
		err(EXIT_FAILURE, "can't stat file");
	fmem =
	    mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (fmem == MAP_FAILED) {
		err(EXIT_FAILURE, "mmap failed");
	}
	array = (char *)fmem;
	for (i = 0; i < st.st_size; i++) {
		printf("%c", array[i]);
		array[i] = toupper(array[i]);
	}
	if (munmap(fmem, st.st_size) < 0)
		err(EXIT_FAILURE, "can't unmmap");
	close(fd);
	exit(EXIT_SUCCESS);
}
