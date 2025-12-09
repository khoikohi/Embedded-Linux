#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_task_queue"

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s <priority> \"<task content>\"\n", argv[0]);
        return 1;
    }

    unsigned int priority = atoi(argv[1]);
    char* message = argv[2];

    mqd_t mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    if (mq_send(mq, message, strlen(message), priority) == -1) {
        perror("mq_send");
        exit(1);
    }

    printf("Sent task (Priority %u): %s\n", priority, message);

    mq_close(mq);
    return 0;
}
