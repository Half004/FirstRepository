#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t s;
pthread_rwlock_t r = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t w = PTHREAD_RWLOCK_INITIALIZER;

void * func(void *arg)
{
	pthread_mutex_lock(&m);
	pthread_spin_lock(&s);
	pthread_rwlock_rdlock(&r);
	pthread_rwlock_wrlock(&w);
	pause();
	pthread_mutex_unlock(&m);
	pthread_spin_unlock(&s);
	pthread_rwlock_unlock(&r);
	pthread_rwlock_unlock(&w);
	return 0;
}

void * func_mutex(void *arg)
{
	pthread_mutex_lock(&m);
	return 0;
}

void * func_spin(void *arg)
{
	pthread_spin_unlock(&s);
	return 0;
}

void * func_rw1(void *arg)
{
	pthread_rwlock_rdlock(&r);
	return 0;
}

void * func_rw2(void *arg)
{
	pthread_rwlock_rdlock(&w);
	return 0;
}

int main(int argc, char **argv)
{
	pthread_spin_init(&s, PTHREAD_PROCESS_PRIVATE);
	pthread_t thread;
	pthread_t t_mutex;
	pthread_t t_spin;
	pthread_t t_rw1;
	pthread_t t_rw2;
	int status_addr;
	pid_t pid = getpid();
	FILE *f = fopen("/home/vi/main.pid", "w");
	fprintf(f, "%d\n", pid);
	fclose(f);
	pthread_create(&thread, NULL, func, NULL);
	sleep(1);
	pthread_create(&t_mutex, NULL, func_mutex, NULL);
	pthread_create(&t_spin, NULL, func_spin, NULL);
	pthread_create(&t_rw1, NULL, func_rw1, NULL);
	pthread_create(&t_rw2, NULL, func_rw2, NULL);
	pthread_join(thread, (void **)&status_addr);
	return 0;
}
	
