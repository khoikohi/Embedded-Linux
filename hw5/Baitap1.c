#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int count = 0;

void sigint_handler(int sig)
{
    count++;
    printf("SIGINT received (%d)\n", count);

    if (count >= 3) {
        printf("Đã nhận 3 lần SIGINT. Thoát chương trình.\n");
        _exit(0);   //để thoát
    }
}

int main()
{
    signal(SIGINT, sigint_handler);

    printf("Chương trình đang chạy... Nhấn Ctrl+C.\n");

    while (1) {
        pause(); // chờ
    }

    return 0;
}
