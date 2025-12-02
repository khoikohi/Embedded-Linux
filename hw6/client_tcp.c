#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    char *msg = "Hello TCP";
    send(sock, msg, strlen(msg), 0);

    char buf[256];
    int n = recv(sock, buf, sizeof(buf), 0);
    buf[n] = 0;

    printf("Client received: %s\n", buf);
    close(sock);
}
