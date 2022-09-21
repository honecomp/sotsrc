#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	int x = 13;

	switch (fork()) {
	case -1:
		err(EXIT_FAILURE, "fork failed!");
	case 0:
		x++;
		printf("I am the child, x is %d\n", x);
		break;
	default:
		x++;
		printf("I am the parent, x is %d\n", x);
	}
	printf("bye bye! x is %d\n", x);
	exit(EXIT_SUCCESS);
}
