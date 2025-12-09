#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <signal.h>
#include <unistd.h>

#define QUEUE_NAME "/my_task_queue"
#define MAX_MSG_SIZE 256

mqd_t mq; 

void cleanup_and_exit(int sig)
{
    printf("\nReceived SIGINT, cleaning up...\n");
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    printf("Queue closed and unlinked. Exiting.\n");
    exit(0);
}

int main()
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;       
    attr.mq_msgsize = MAX_MSG_SIZE;  
    attr.mq_curmsgs = 0;

    signal(SIGINT, cleanup_and_exit);

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0666, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    printf("Worker started. Waiting for tasks...\n");

    char buffer[MAX_MSG_SIZE];
    unsigned int prio;

    while (1) {
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_MSG_SIZE, &prio);
        if (bytes_read >= 0) {
            buffer[bytes_read] = '\0';
            printf("Processing task (Priority: %u): %s\n", prio, buffer);
            sleep(1);
        } else {
            perror("mq_receive");
        }
    }

    return 0;
}
