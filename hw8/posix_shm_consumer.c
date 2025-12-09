#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shared_mem"
#define SHM_SIZE 4096

typedef struct {
    int id;
    char name[256];
    double price;
} product_t;

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    void *ptr = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    product_t prod;
    memcpy(&prod, ptr, sizeof(product_t));

    printf("Consumer: read product id=%d, name=%s, price=%.2f\\n",
           prod.id, prod.name, prod.price);

    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
    }

    munmap(ptr, SHM_SIZE);
    close(shm_fd);

    return 0;
}
