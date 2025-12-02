#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // 1. Tạo pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // 2. Tạo tiến trình con 1 chạy ls -l
    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Child 1
        dup2(fd[1], STDOUT_FILENO); // stdout -> pipe (đầu ghi)

        close(fd[0]); // không dùng đầu đọc
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    }

    // 3. Tạo tiến trình con 2 chạy wc -l
    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Child 2
        dup2(fd[0], STDIN_FILENO); // stdin <- pipe (đầu đọc)

        close(fd[1]); // không dùng đầu ghi
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(1);
    }

    // 4. Tiến trình cha đóng cả pipe
    close(fd[0]);
    close(fd[1]);

    // 5. Chờ hai tiến trình hoàn thành
    wait(NULL);
    wait(NULL);

    return 0;
}
