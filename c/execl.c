#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>

int
main(int argc, char *argv[])
{

	fprintf(stderr, "hello!\n");
	execl("/bin/ls", "myls", "/tmp", NULL);
	fprintf(stderr, "bye!\n");
	err(EXIT_FAILURE, "exec failed");
}
