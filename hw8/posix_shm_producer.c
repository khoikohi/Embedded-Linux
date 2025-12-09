#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // for O_* constants
#include <sys/stat.h>   // for mode constants
#include <sys/mman.h>
#include <unistd.h>     // for ftruncate
#include <string.h>

#define SHM_NAME "/my_shared_mem"
#define SHM_SIZE 4096

typedef struct {
    int id;
    char name[256];
    double price;
} product_t;

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    void *ptr = mmap(NULL, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    product_t prod;
    prod.id = 123;
    strncpy(prod.name, "Sản phẩm", sizeof(prod.name)-1);
    prod.name[sizeof(prod.name)-1] = '\\0';
    prod.price = 2.5;

    memcpy(ptr, &prod, sizeof(product_t));

    printf("Producer: wrote product id=%d, name=%s, price=%.2f\\n",
           prod.id, prod.name, prod.price);

    sleep(5);

    munmap(ptr, SHM_SIZE);
    close(shm_fd);

    return 0;
}
