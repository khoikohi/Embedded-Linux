#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9001);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    char *msg = "Hello UDP";

    sendto(fd, msg, strlen(msg), 0, (struct sockaddr*)&addr, sizeof(addr));

    char buf[256];
    socklen_t len = sizeof(addr);

    int n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
    buf[n] = 0;

    printf("Client received: %s\n", buf);
    close(fd);
}
