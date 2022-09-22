#include <stdlib.h>
#include <stdio.h>

/* una funcion impar mal hecha! */

int
esimpar(int x)
{
	switch (x) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 9:
		return 1;
	case 0:
	case 2:
	case 4:
	case 6:
	case 8:
		return 0;
	default:
		return -1;
	}
}

int
main(int argc, char *argv[])
{
	int x;

	x = 3;
	switch (esimpar(x)) {
	case 1:
		printf("es impar!\n");
		break;
	case 0:
		printf("es par!\n");
		break;
	default:
		printf("error en impar");
	}
	exit(EXIT_SUCCESS);
}
