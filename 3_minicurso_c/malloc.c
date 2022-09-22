#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	char *str;

	str = malloc(100);
	if (str == NULL) {
		fprintf(stderr, "bad malloc");
		exit(EXIT_FAILURE);
	}
	snprintf(str, 100, "Escribo en una string");
	printf("%s\n", str);
	free(str);
	exit(EXIT_SUCCESS);
}
