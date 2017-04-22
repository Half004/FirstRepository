#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define SHM_SIZE 1024*1024

int main(int argc, char **argv)
{
	int fd = shm_open("/test.shm", O_CREAT | O_RDWR, 0666);
	ftruncate(fd, SHM_SIZE);
	char *data = (char *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	char c = 13;
	for (unsigned int i = 0; i < SHM_SIZE; ++i)
		data[i] = c;
	munmap(data, SHM_SIZE);
	close(fd);	
	return 0;
}
