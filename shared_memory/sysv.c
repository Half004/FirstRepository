#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024*1024

int main(int argc, char **argv)
{	
	key_t key = ftok("/tmp/mem.temp", 1);
	int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
	char *data = shmat(shmid, NULL, 0);
	char c = 42;
	for (unsigned int i = 0; i < SHM_SIZE; ++i)
		*data++ = c;
	shmdt(data);
	return 0;
}
