#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void
handler(int number)
{
	switch (number) {
	case SIGINT:
		fprintf(stderr, "SIGINT received!\n");
		break;
	case SIGTERM:
		fprintf(stderr, "SIGTERM received!\n");
		break;
	default:
		fprintf(stderr, "other: %d\n", number);
	}
}

int
main(int argc, char *argv[])
{
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	// this won't work... you cannot ignore sigkill
	signal(SIGKILL, SIG_IGN);

	for (;;) {
		sleep(1);
		printf("I am here! my PID is: %d\n", getpid());
	}
}
