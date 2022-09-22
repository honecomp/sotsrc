#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	int x = 13;

	printf("x: %d", x);
	for (;;) {
		;
	}
	exit(EXIT_SUCCESS);
}
