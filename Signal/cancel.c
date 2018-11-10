#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *loop(void *arg) {
	printf("thread started\n");
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	for (;;) { }
	printf("thread terminated\n");
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t pid;
	pthread_create(&pid, NULL, loop, NULL);
	pthread_cancel(pid);
	pthread_join(pid, NULL);
	printf("thread joined\n");
}

