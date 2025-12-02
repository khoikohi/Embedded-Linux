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

    connect(fd, (struct sockaddr*)&addr, sizeof(addr));

    char *msg = "Hello UNIX STREAM";
    send(fd, msg, strlen(msg), 0);

    char buf[256];
    int n = recv(fd, buf, sizeof(buf), 0);
    buf[n] = 0;

    printf("Client received: %s\n", buf);
    close(fd);
}
