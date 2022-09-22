#include <stdio.h>
#include <stdlib.h>
int
main(int argc, char *argv[], char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++) {
		printf("envp[%d]: %s\n", i, envp[i]);
	}
	exit(EXIT_SUCCESS);
}
