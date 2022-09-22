#include <stdio.h>
#include <stdlib.h>

void
f(int *i)
{
	*i = (int)random();
}

int
main()
{
	const int x = 33;
	int y;

	f(&y - sizeof(int));
	printf("x is %d\n", x);
	exit(0);
}
