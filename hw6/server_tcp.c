#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9000);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    int client_fd = accept(server_fd, NULL, NULL);

    char buf[256];
    int n = recv(client_fd, buf, sizeof(buf), 0);
    buf[n] = 0;

    printf("Server received: %s\n", buf);

    send(client_fd, buf, n, 0);

    close(client_fd);
    close(server_fd);
}
