#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	char *args[3];

	args[0] = "myls";
	args[1] = "/tmp";
	args[2] = NULL;

	fprintf(stderr, "hello!\n");
	execv("/bin/ls", args);
	fprintf(stderr, "bye!\n");
	exit(EXIT_FAILURE);
}
