#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int x;
	int y;

	x = 1;
	x++;
	printf("El valor de x (decimal): %d\n", x);
	--x;
	printf("El valor de x (decimal): %d\n", x);
	y = x + 1;
	printf("El valor de y (decimal): %d\n", y);

	x = 0xff;
	printf("El valor de x (hexa): %x\n", x);
	x = ~x;
	printf("El valor de x (hexa): %x\n", x);
	x = x << 4;
	printf("El valor de x (hexa): %x\n", x);
	y = 0xfff;
	x = x | y;
	printf("El valor de x (hexa): %x\n", x);

	y = x && 1;
	printf("El valor de y (hexa): %x\n", y);
	y = 0 && x;
	printf("El valor de y (hexa): %x\n", y);

	/* ahora el operador terniario */

	y = x == 0xffffffff ? 666 : 111;
	printf("El valor de y (decimal): %d\n", y);

	exit(EXIT_SUCCESS);
}
