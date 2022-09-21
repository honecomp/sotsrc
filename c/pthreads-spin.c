#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>

enum {
	Nthreads = 200,
	Nrounds = 10000,
};

int counter;
pthread_spinlock_t lk;

void *
fn(void *p)
{
	int i;

	for (i = 0; i < Nrounds; i++) {
		pthread_spin_lock(&lk);
		counter++;
		pthread_spin_unlock(&lk);
	}
	return NULL;
}

int
main(int argc, char *argv[])
{
	pthread_t thread[Nthreads];
	int i;

	if (pthread_spin_init(&lk, PTHREAD_PROCESS_SHARED) != 0) {
		warnx("can't init lock");
		return 1;
	}
	for (i = 0; i < Nthreads; i++) {
		if (pthread_create(&thread[i], NULL, fn, NULL) != 0) {
			warnx("error creating thread");
			return 1;
		}
	}
	for (i = 0; i < Nthreads; i++) {
		if (pthread_join(thread[i], NULL) != 0) {
			warnx("error joining thread");
			return 1;
		}
	}
	pthread_spin_destroy(&lk);
	if (counter != Nthreads * Nrounds) {
		fprintf(stderr,
			"MAIN: counter is %d, should be %d\n",
			counter, Nthreads * Nrounds);
	} else {
		fprintf(stderr, "MAIN: counter is %d, OK\n", counter);
	}
	return 0;
}
