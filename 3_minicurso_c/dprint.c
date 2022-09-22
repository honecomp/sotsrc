#include <stdlib.h>
#include <stdio.h>

extern int debugflag;

void
dprint(char *s)
{
	if (debugflag)
		printf("DEBUGGING: %s \n", s);
}
