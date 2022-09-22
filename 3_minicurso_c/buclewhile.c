#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int x = 0;

	while (x < 10) {
		printf("x es %d\n", x);
		x++;
	}
	exit(EXIT_SUCCESS);
}
