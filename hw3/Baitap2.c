#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    setenv("MY_COMMAND", "ls", 1);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        char *cmd = getenv("MY_COMMAND");

        if (cmd == NULL) {
            fprintf(stderr, "MY_COMMAND not set\n");
            exit(1);
        }

        printf("Child: executing command from MY_COMMAND = %s\n", cmd);

        execlp(cmd, cmd, NULL);

        perror("execlp failed");
        exit(1);
    } 
    else {
        wait(NULL);
        printf("Parent: child finished execution.\n");
    }

    return 0;
}
