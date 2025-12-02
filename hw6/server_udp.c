#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9001);

    bind(fd, (struct sockaddr*)&addr, sizeof(addr));

    char buf[256];
    struct sockaddr_in client;
    socklen_t clen = sizeof(client);

    int n = recvfrom(fd, buf, sizeof(buf), 0, 
                     (struct sockaddr*)&client, &clen);
    buf[n] = 0;

    printf("Server received: %s\n", buf);

    sendto(fd, buf, n, 0, (struct sockaddr*)&client, clen);

    close(fd);
}
