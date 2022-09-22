#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	char *p;

	p = (char *)0x18;
	printf("s.x :%d\n", *p);
}
