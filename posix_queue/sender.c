#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#define MAX_SIZE 256
#define QUEUE_NAME "/test.mq"

int main(int argc, char **argv)
{
    mqd_t mq;
    char buffer[MAX_SIZE];

    /* open the mail queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    strcpy(buffer, "Test message");
    mq_send(mq, buffer, MAX_SIZE, 0);
    
    return 0;
}
