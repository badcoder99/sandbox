#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCERS	(10)
#define FILTERS		(3)
#define CONSUMERS	(5)
#define BUFFER		(25)
#define NUMBERS		(100)
#define DONE		(-1)

struct Buffer {
	int in, out, id, remain, data[BUFFER];
	pthread_mutex_t in_sync, out_sync, sync;
	pthread_cond_t in_cond, out_cond;
	sem_t empty, used;
};

struct Buffer *init(int threads) {
	struct Buffer *buf = malloc(sizeof(struct Buffer));
	buf->in = 0;
	buf->out = 0;
	buf->id = 0;
	buf->remain = threads;
	pthread_mutex_init(&buf->in_sync, NULL);
	pthread_mutex_init(&buf->out_sync, NULL);
	pthread_mutex_init(&buf->sync, NULL);
	pthread_cond_init(&buf->in_cond, NULL);
	pthread_cond_init(&buf->out_cond, NULL);
	sem_init(&buf->empty, 0, BUFFER);
	sem_init(&buf->used, 0, 0);
	return buf;
}

void destroy(struct Buffer *buf) {
	pthread_mutex_destroy(&buf->in_sync);
	pthread_mutex_destroy(&buf->out_sync);
	pthread_mutex_destroy(&buf->sync);
	pthread_cond_destroy(&buf->in_cond);
	pthread_cond_destroy(&buf->out_cond);
	sem_destroy(&buf->empty);
	sem_destroy(&buf->used);
	free(buf);
}

void push(struct Buffer *buf, int val) {
	pthread_mutex_lock(&buf->in_sync);
	while (sem_trywait(&buf->empty)) {
		pthread_cond_wait(&buf->in_cond, &buf->in_sync);
	}
	buf->data[buf->in] = val;
	buf->in = (buf->in + 1) % BUFFER;
	pthread_mutex_unlock(&buf->in_sync);
	sem_post(&buf->used);
	pthread_cond_signal(&buf->out_cond);
}

int pop(struct Buffer *buf) {
	pthread_mutex_lock(&buf->out_sync);
	while (sem_trywait(&buf->used)) {
		if (buf->remain) {
			pthread_cond_wait(&buf->out_cond, &buf->out_sync);
		}
		else {
			pthread_mutex_unlock(&buf->out_sync);
			return DONE;
		}	
	}
	int val = buf->data[buf->out];
	buf->out = (buf->out + 1) % BUFFER;
	pthread_mutex_unlock(&buf->out_sync);
	sem_post(&buf->empty);
	pthread_cond_signal(&buf->in_cond);
	return val;
}

void done(struct Buffer *buf) {
	pthread_mutex_lock(&buf->sync);	
	buf->remain--;
	pthread_mutex_unlock(&buf->sync);
	pthread_cond_broadcast(&buf->out_cond);
}

void *consumer(void *arg) {
	struct Buffer *fbuf = ((struct Buffer**)arg)[1];
	pthread_mutex_lock(&fbuf->sync);
	int id = fbuf->id++;
	pthread_mutex_unlock(&fbuf->sync);
	FILE *out;
	char str[80];
	sprintf(str, "num%d.txt", id);
	out = fopen(str, "w");
	int flag = 1;
	while (flag) {	
		pthread_mutex_lock(&fbuf->out_sync);
		while (sem_trywait(&fbuf->used)) {
			if (fbuf->remain) {
				pthread_cond_wait(&fbuf->out_cond, &fbuf->out_sync);
			}
			else {
				pthread_mutex_unlock(&fbuf->out_sync);
				flag = 0;
				break;
			}	
		}
		if (flag) {
			int val = fbuf->data[fbuf->out];
			if (val % (CONSUMERS * 2) == id * 2) {
				fbuf->out = (fbuf->out + 1) % BUFFER;
				pthread_mutex_unlock(&fbuf->out_sync);
				sem_post(&fbuf->empty);
				pthread_cond_signal(&fbuf->in_cond);
				fprintf(out, "%d\n", val);
			}
			else {
				sem_post(&fbuf->used);
				pthread_mutex_unlock(&fbuf->out_sync);
			}
		}
	}
	fclose(out);
	pthread_exit(NULL);
}

void *filter(void *arg) {
	struct Buffer *pbuf = ((struct Buffer**)arg)[0];
	struct Buffer *fbuf = ((struct Buffer**)arg)[1];
	int val;
	while ((val = pop(pbuf)) != DONE) {
		if (val % 2 == 0) {
			push(fbuf, val);
		}
	}
	done(fbuf);
	pthread_exit(NULL);
}

void *producer(void *arg) {
	struct Buffer *pbuf = ((struct Buffer**)arg)[0];
	pthread_mutex_lock(&pbuf->sync);
	int id = pbuf->id++;
	pthread_mutex_unlock(&pbuf->sync);
	for (int i = 0; i < NUMBERS; ++i) {
		push(pbuf, i + NUMBERS * id);
	}
	done(pbuf);
	pthread_exit(NULL);
}

void check() {
	int n = (PRODUCERS * NUMBERS) / 2;
	int *nums = malloc(sizeof(int) * n);
	int *ptr = nums;
	char str[80];
	FILE *in;
	for (int id = 0; id < CONSUMERS; ++id) {
		sprintf(str, "num%d.txt", id);
		in = fopen(str, "r");
		int val;
		while (fscanf(in, "%d", &val) != EOF) {
			*ptr++ = val;
		}
		fclose(in);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (nums[j] > nums[j + 1]) {
				int temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (nums[i] != i * 2) {
			printf("error\n");
		}
	}
	printf("pass\n");
	free(nums);
}
	
int main() {
	pthread_t producers[PRODUCERS];
	pthread_t filters[FILTERS];
	pthread_t consumers[CONSUMERS];
	struct Buffer **buf = malloc(sizeof(struct Buffer*) * 2);
	buf[0] = init(PRODUCERS);
	buf[1] = init(FILTERS);

	for (int i = 0; i < CONSUMERS; ++i) {
		pthread_create(consumers + i, NULL, consumer, (void*)buf);
	}
	for (int i = 0; i < FILTERS; ++i) {
		pthread_create(filters + i, NULL, filter, (void*)buf);
	}
	for (int i = 0; i < PRODUCERS; ++i) {
		pthread_create(producers + i, NULL, producer, (void*)buf);
	}
	for (int i = 0; i < PRODUCERS; ++i) {
		pthread_join(producers[i], NULL);
	}
	for (int i = 0; i < FILTERS; ++i) {
		pthread_join(filters[i], NULL);
	}
	for (int i = 0; i < CONSUMERS; ++i) {
		pthread_join(consumers[i], NULL);
	}
	check();
	destroy(buf[0]);
	destroy(buf[1]);
	free(buf);	
}

