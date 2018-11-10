#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool flag;

void stop(int sig) {
	flag = false;
}

void *loop(void *arg) {
	printf("thread started\n");
	while(flag) {
		sleep(1);
	}
	printf("thread terminated\n");
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t pid;
	signal(SIGUSR1, stop);
	flag = true;
	printf("thread created\n");
	pthread_create(&pid, NULL, loop, NULL);
	sleep(1);
	printf("kill signal sent\n");
	pthread_kill(pid, SIGUSR1);
	pthread_join(pid, NULL);
	printf("thread joined\n");
}

