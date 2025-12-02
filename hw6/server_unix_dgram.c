#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/unix_dgram_server.sock"
#define CLIENT_PATH "/tmp/unix_dgram_client.sock"

int main() {
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);

    struct sockaddr_un server = {0}, client = {0};
    server.sun_family = AF_UNIX;
    client.sun_family = AF_UNIX;
    strcpy(server.sun_path, SERVER_PATH);
    strcpy(client.sun_path, CLIENT_PATH);

    unlink(SERVER_PATH);
    unlink(CLIENT_PATH);

    bind(fd, (struct sockaddr*)&server, sizeof(server));

    char buf[256];
    socklen_t len = sizeof(client);

    int n = recvfrom(fd, buf, sizeof(buf), 0,
                     (struct sockaddr*)&client, &len);
    buf[n] = 0;

    printf("Server received: %s\n", buf);

    sendto(fd, buf, n, 0,
           (struct sockaddr*)&client, len);

    close(fd);
}
