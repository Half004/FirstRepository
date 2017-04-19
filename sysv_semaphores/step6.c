#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SET_SIZE 2

int main(int argc, char **argv)
{
    key_t key;
    int semid;
    key = ftok("/tmp/sem.tmp", 1);
    semid = semget(key, SET_SIZE, 0666 | IPC_CREAT);
    union semun {
    int val;
    struct semid_ds *buf;
    ushort array [SET_SIZE];
    } arg;
    for (size_t i = 0; i < SET_SIZE; ++i)
    {
        //arg.val = i;
        semctl(semid, i, SETVAL, i);   
    }
    for (size_t i = 0; i < SET_SIZE; ++i)
    {
        int val = semctl(semid, i, GETVAL, 0);
        printf("Semaphore %u, value = %d\n", i, val);
    }
    return 0;
}
//    
//    struct semid_ds semid_ds;
//    union semun {
//    int val;
//    struct semid_ds *buf;
//    ushort array [MAXSETSIZE];
//    } arg;
//    /* Инициализация указателя на структуру данных */
//    arg.buf = &semid_ds;
    
