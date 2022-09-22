#include <stdlib.h>
#include <stdio.h>

void
dameletra(char *c)
{
	*c = 'A';
}

int
main(int argc, char *argv[])
{
	char c = 'b';

	dameletra(&c);
	printf("c es %c\n", c);
	exit(EXIT_SUCCESS);
}
