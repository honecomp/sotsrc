#include <stdlib.h>
#include <stdio.h>
/*

gcc -c -Wall -Wshadow mainargs.c
gcc -o mainargs mainargs.o
./mainargs uno blablito
*/

int
main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++)
		printf("argv+%d: %p\n", i, argv + i);
	for (i = 0; i < argc; i++)
		printf("%p arg[%d]: %s\n", argv[i], i, argv[i]);
	exit(EXIT_SUCCESS);
}
