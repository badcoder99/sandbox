#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX	(20)
#define DONE	(-1)

struct Buffer {
	int in, out, cnt, data[MAX];
	pthread_mutex_t lock;
} b1, b2;

void init(struct Buffer *ptr) {
	ptr->in = 0;
	ptr->out = 0;
	ptr->cnt = 0;
	pthread_mutex_init(&ptr->lock, NULL);
}

void push(struct Buffer *ptr, int val) {
	while (ptr->cnt == MAX);
	pthread_mutex_lock(&ptr->lock);
	ptr->data[ptr->in] = val;
	ptr->cnt++;
	pthread_mutex_unlock(&ptr->lock);
	ptr->in = (ptr->in + 1) % MAX;
}

int pop(struct Buffer *ptr) {
	int val;
	while (ptr->cnt == 0);
	pthread_mutex_lock(&ptr->lock);
	val = ptr->data[ptr->out];
	ptr->cnt--;
	pthread_mutex_unlock(&ptr->lock);
	ptr->out = (ptr->out + 1) % MAX;
	return val;
}

void *consumer(void *ptr) {
	int flag = 1;
	while (flag) {
		int num = pop(&b2);
		if (num == DONE) {
			flag = 0;
		}
		else {
			printf("%d: ", num);
			int nums = 0, val;
			while (val = pop(&b2)) {
				printf("%d ", val);
				nums++;
			}
			if (nums == 0) {
				printf("%d", num);
			}
			printf("\n");
		}
	}
	pthread_exit(NULL);
}

void factor(int num) {
	push(&b2, num);
	int div = 2;
	while (num != 1) {
		while (num % div == 0) {
			push(&b2, div);
			num /= div;
		}
		++div;
	}
	push(&b2, 0);
}

void *producer(void *ptr) {
	int flag = 1;
	while (flag) {
		int num = pop(&b1);
		if (num == DONE) {
			flag = 0;
			push(&b2, DONE);
		}
		else {
			factor(num);
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t t1, t2;
	init(&b1);
	init(&b2);
	pthread_create(&t1, NULL, consumer, NULL);
	pthread_create(&t2, NULL, producer, NULL);
	for (int i = 1; i < argc; ++i) {
		int num = atoi(argv[i]);
		if (num <= 0) {
			printf("Invalid: \'%s\'\n", argv[i]);
		}
		else {
			push(&b1, num);
		}
	}
	push(&b1, DONE);
	pthread_join(t2, NULL);
	pthread_join(t1, NULL);	
	pthread_mutex_destroy(&b1.lock);
	pthread_mutex_destroy(&b2.lock);
	return 0;
}

