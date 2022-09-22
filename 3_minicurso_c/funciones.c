#include <stdlib.h>
#include <stdio.h>

/* definicion de funcion */
int
suma(int x, int y)
{
	return x + y;
}

/* definicion de funcion */

void
saludo(int x)
{
	printf("Hola %d\n", x);
}

/* declaracion de una funcion */

int damenumero(void);

int
main(int argc, char *argv[])
{
	int x;

	x = suma(3, 4);
	saludo(x);
	x = damenumero();
	saludo(x);
	exit(EXIT_SUCCESS);
}

int
damenumero(void)
{
	return -3;
}
