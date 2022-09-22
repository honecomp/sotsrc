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
	// just an example, fprintf is not async-signal-safe
	fprintf(stderr, "I am the handler\n");
}

void
printpending()
{
	sigset_t pending;
	int i;

	sigemptyset(&pending);
	sigpending(&pending);
	fprintf(stderr, "Pending signals:");
	for (i = 1; i < NSIG; i++) {
		if (sigismember(&pending, i)) {
			fprintf(stderr, " %02d", i);
		}
	}
	fprintf(stderr, "\n");
}

int
main(int argc, char *argv[])
{
	sigset_t set;

	fprintf(stderr, "Blocking SIGINT for 10 seconds\n");
	signal(SIGINT, handler);
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);
	sleep(10);

	printpending();

	fprintf(stderr, "Unblocking SIGINT\n");
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	fprintf(stderr, "Main done, bye bye!\n");
	exit(EXIT_SUCCESS);
}
