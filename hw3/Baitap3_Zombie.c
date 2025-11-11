#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        printf("Child: PID = %d exiting now...\n", getpid());
        exit(0);
    } 
    else {
        printf("Parent: PID = %d, child PID = %d\n", getpid(), pid);
        printf("Parent is sleeping, not calling wait()\n");
        sleep(30);
    }

    return 0;
}
