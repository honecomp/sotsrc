#include <stdlib.h>
#include <stdio.h>

int
esimpar(int x)
{
	return x % 2;
}

int
main(int argc, char *argv[])
{
	int x;

	x = 3;
	if (esimpar(x))
		printf("es impar!\n");
	else
		printf("es par!\n");
	exit(EXIT_SUCCESS);
}
