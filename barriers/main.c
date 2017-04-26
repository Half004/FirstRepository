#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bp;

void * func_cond(void *arg)
{
	pthread_cond_wait(&cond, &m);
}

void * func_barrier(void *arg)
{
	pthread_barrier_wait(&bp);
	return 0;
}

int main(int argc, char **argv)
{
	pid_t pid = getpid();
	FILE *f = fopen("/home/vi/main.pid", "w");
	fprintf(f, "%d\n", pid);
	fclose(f);
	pthread_barrier_init(&bp, NULL, 2);
	pthread_t t_cond;
	pthread_t t_barrier;
	pthread_create(&t_cond, NULL, func_cond, NULL);
	pthread_create(&t_barrier, NULL, func_barrier, NULL);
	pthread_join(t_barrier, NULL);
	pause();
	pthread_cond_signal(&cond);
	pthread_join(t_cond, NULL);
	return 0;
}
