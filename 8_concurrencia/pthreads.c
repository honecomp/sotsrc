#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>

void *
fn(void *p)
{
	fprintf(stderr, "Hi! I'm fn\n");
	return NULL;
}

int
main(int argc, char *argv[])
{
	pthread_t thread;

	if (pthread_create(&thread, NULL, fn, NULL) != 0) {
		warnx("error creating thread");
		return 1;
	}
	fprintf(stderr, "Hi! I'm main\n");
	if (pthread_join(thread, NULL) != 0) {
		warnx("error joining thread");
		return 1;
	}
	return 0;
}
