#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int seconds = 0;

void alarm_handler(int sig)
{
    seconds++;
    printf("Timer: %d seconds\n", seconds);

    if (seconds >= 10) {
        printf("Hết 10 giây. Thoát.\n");
        _exit(0);
    }

    alarm(1); // đặt lại hẹn giờ
}

int main()
{
    signal(SIGALRM, alarm_handler);
    alarm(1);

    while (1) pause();
}
