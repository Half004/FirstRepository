#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void * func(void *arg)
{
	pause();
	return 0;
}

int main(int argc, char **argv)
{
	pthread_t thread;
	int status_addr;
	pid_t pid = getpid();
	FILE *f = fopen("home/vi/main.pid", "w");
	fprintf(f, "%d\n", pid);
	fclose(f);
	pthread_create(&thread, NULL, func, NULL);
	pthread_join(thread, (void **)&status_addr);
	return 0;
}
	
