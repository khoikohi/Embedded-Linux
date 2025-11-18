#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>

volatile sig_atomic_t sigint_flag = 0;
volatile sig_atomic_t sigterm_flag = 0;

void sigint_handler(int sig) {
    sigint_flag = 1;
}

void sigterm_handler(int sig) {
    sigterm_flag = 1;
}

int main()
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    printf("Chương trình sẵn sàng. Nhập dữ liệu hoặc gửi tín hiệu.\n");

    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        struct timeval tv = {1, 0}; // 1 giây

        int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

        if (sigint_flag) {
            printf("SIGINT received.\n");
            sigint_flag = 0;
        }

        if (sigterm_flag) {
            printf("SIGTERM received. Thoát chương trình.\n");
            break;
        }

        if (ret > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
            char buffer[256];
            fgets(buffer, sizeof(buffer), stdin);
            printf("Bạn đã nhập: %s", buffer);
        }
    }
}
