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
        while (1) {
            printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
            sleep(2);
        }
    } 
    else {
        printf("Parent: exiting now.\n");
        exit(0);
    }

    return 0;
}
