#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	char c = 'A';
	char *ptr;
	char d;

	ptr = &c;
	d = *ptr;
	printf("c: %c *ptr: %c d: %c\n", c, *ptr, d);

	*ptr = 'B';
	printf("c: %c *ptr: %c d: %c\n", c, *ptr, d);

	exit(EXIT_SUCCESS);
}
