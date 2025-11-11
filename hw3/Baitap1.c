#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        printf("Child process:\n");
        printf("  PID = %d\n", getpid());
        printf("  Parent PID = %d\n", getppid());
        exit(10);
    } 
    else {
        printf("Parent process:\n");
        printf("  PID = %d\n", getpid());
        printf("  Child PID = %d\n", pid);

        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child exited normally with code = %d\n", WEXITSTATUS(status));
        } else {
            printf("Child exited abnormally\n");
        }
    }

    return 0;
}
