#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig)
{
    printf("Child: Received signal from parent\n");
}

int main()
{
    pid_t pid = fork();

    if (pid == 0) {
        signal(SIGUSR1, handler);
        while (1) pause();
    }
    else {
        for (int i = 0; i < 5; i++) {
            sleep(2);
            printf("Parent: Gửi tín hiệu %d\n", i+1);
            kill(pid, SIGUSR1);
        }

        printf("Parent: hoàn thành. Thoát.\n");
        kill(pid, SIGTERM);
        wait(NULL);
    }
    return 0;
}
