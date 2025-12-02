#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/unix_stream.sock"

int main() {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    unlink(SOCK_PATH);
    bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(fd, 1);

    int cfd = accept(fd, NULL, NULL);

    char buf[256];
    int n = recv(cfd, buf, sizeof(buf), 0);
    buf[n] = 0;

    printf("Server received: %s\n", buf);
    send(cfd, buf, n, 0);

    close(cfd);
    close(fd);
}
