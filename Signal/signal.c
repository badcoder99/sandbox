#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void f(int sig) {
	printf("signaled\n");
}

int main() {
	signal(SIGUSR1, f);
	for (int i = 0; i < 5; ++i) {
		raise(SIGUSR1);
		sleep(1);
	}
}

