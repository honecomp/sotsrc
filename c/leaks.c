#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
	int i;
	int max;
	char *p;

	max = 0;
	for (i = 1; i < argc; i++) {
		if (strlen(argv[i]) > max) {
			max = strlen(argv[i]);
			p = malloc(max + 1);	// leak!
			strcpy(p, argv[i]);
		}
		printf("[%d] %s\n", i, argv[i]);
	}
	printf("The largest argument is: %s\n", p);
	free(p);
	exit(EXIT_SUCCESS);
}
