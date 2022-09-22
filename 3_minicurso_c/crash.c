#include <stdio.h>
#include <stdlib.h>

struct Patata {
	int x;
	int y;
};
typedef struct Patata Patata;

void
crasher(Patata * s, int z)
{
	int n;

	n = z + 2;
	printf("n :%d\n", n);
	printf("s.x :%d\n", s->x);
}

int
main(int argc, char *argv[])
{
	Patata *s;

	s = (Patata *) 0x18;
	crasher(s, 12);
}
