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

enum {
	Bsize = 1024,
	Timeout = 5,
};

void
handler(int number)
{
	// just an example, fpritnf is not async-signal-safe
	fprintf(stderr, "This is the handler, is the syscall restarted?\n");
}

int
main(int argc, char *argv[])
{
	int setflag;
	char buf[Bsize];
	int nr;

	if (argc != 2) {
		err(EXIT_FAILURE, "usage: timeout [0|1]");
	}
	setflag = atoi(argv[1]);
	if (setflag != 0 && setflag != 1) {
		err(EXIT_FAILURE, "Bad argument");
	}

	signal(SIGALRM, handler);
	siginterrupt(SIGALRM, setflag);

	alarm(Timeout);
	nr = read(0, buf, sizeof(buf) - 1);
	alarm(0);
	if (nr < 0) {
		if (errno == EINTR) {
			fprintf(stdout, "timeout!\n");
		} else {
			err(EXIT_FAILURE, "read error");
		}
	} else {
		buf[nr] = '\0';
		printf("read: %s", buf);
	}
	exit(EXIT_SUCCESS);
}
