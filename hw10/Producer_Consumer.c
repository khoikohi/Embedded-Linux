#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE 10

typedef struct {
    int vegan_tray[SIZE];
    int nonvegan_tray[SIZE];

    int vegan_in, vegan_out;
    int nonveg_in, nonveg_out;

    sem_t vegan_mutex, vegan_empty, vegan_full;
    sem_t non_mutex, non_empty, non_full;

} shared_data;


void chef_donatello(shared_data *shm) {
    char *menu[] = {
        "Fettuccine Chicken Alfredo",
        "Garlic Sirloin Steak"
    };

    while (1) {
        sleep(rand() % 5 + 1);

        int idx = rand() % 2;
        int dish = 2;

        sem_wait(&shm->non_empty);
        sem_wait(&shm->non_mutex);

        shm->nonvegan_tray[shm->nonveg_in] = dish;
        shm->nonveg_in = (shm->nonveg_in + 1) % SIZE;

        printf("[Donatello] Cooked: %s → placed on NON-VEGAN tray\n", menu[idx]);
        fflush(stdout);

        sem_post(&shm->non_mutex);
        sem_post(&shm->non_full);
    }
}

void chef_portecelli(shared_data *shm) {
    char *menu[] = {
        "Pistachio Pesto Pasta",
        "Avocado Fruit Salad"
    };

    while (1) {
        sleep(rand() % 5 + 1);

        int idx = rand() % 2;
        int dish = 1;

        sem_wait(&shm->vegan_empty);
        sem_wait(&shm->vegan_mutex);

        shm->vegan_tray[shm->vegan_in] = dish;
        shm->vegan_in = (shm->vegan_in + 1) % SIZE;

        printf("[Portecelli] Cooked: %s → placed on VEGAN tray\n", menu[idx]);
        fflush(stdout);

        sem_post(&shm->vegan_mutex);
        sem_post(&shm->vegan_full);
    }
}


void customer_nonveg(shared_data *shm) {
    while (1) {
        sem_wait(&shm->non_full);
        sem_wait(&shm->non_mutex);

        int dish = shm->nonvegan_tray[shm->nonveg_out];
        shm->nonvegan_tray[shm->nonveg_out] = 0;
        shm->nonveg_out = (shm->nonveg_out + 1) % SIZE;

        printf("[Customer 1] Took NON-VEGAN dish\n");
        fflush(stdout);

        sem_post(&shm->non_mutex);
        sem_post(&shm->non_empty);

        sleep(rand() % 6 + 10);   
    }
}

void customer_vegan(shared_data *shm) {
    while (1) {
        sem_wait(&shm->vegan_full);
        sem_wait(&shm->vegan_mutex);

        int dish = shm->vegan_tray[shm->vegan_out];
        shm->vegan_tray[shm->vegan_out] = 0;
        shm->vegan_out = (shm->vegan_out + 1) % SIZE;

        printf("[Customer 2] Took VEGAN dish\n");
        fflush(stdout);

        sem_post(&shm->vegan_mutex);
        sem_post(&shm->vegan_empty);

        sleep(rand() % 6 + 10);
    }
}

void customer_hybrid(shared_data *shm) {
    while (1) {
        sem_wait(&shm->vegan_full);
        sem_wait(&shm->vegan_mutex);

        shm->vegan_tray[shm->vegan_out] = 0;
        shm->vegan_out = (shm->vegan_out + 1) % SIZE;

        printf("[Hybrid] Took VEGAN dish\n");

        sem_post(&shm->vegan_mutex);
        sem_post(&shm->vegan_empty);

        sem_wait(&shm->non_full);
        sem_wait(&shm->non_mutex);

        shm->nonvegan_tray[shm->nonveg_out] = 0;
        shm->nonveg_out = (shm->nonveg_out + 1) % SIZE;

        printf("[Hybrid] Took NON-VEGAN dish\n");

        sem_post(&shm->non_mutex);
        sem_post(&shm->non_empty);

        fflush(stdout);

        sleep(rand() % 6 + 10);
    }
}


int main() {
    srand(time(NULL));

    shared_data *shm = mmap(NULL, sizeof(shared_data),
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS,
                            -1, 0);

    for (int i = 0; i < SIZE; i++) {
        shm->vegan_tray[i] = 0;
        shm->nonvegan_tray[i] = 0;
    }

    shm->vegan_in = shm->vegan_out = 0;
    shm->nonveg_in = shm->nonveg_out = 0;

    sem_init(&shm->vegan_mutex, 1, 1);
    sem_init(&shm->vegan_empty, 1, SIZE);
    sem_init(&shm->vegan_full, 1, 0);

    sem_init(&shm->non_mutex, 1, 1);
    sem_init(&shm->non_empty, 1, SIZE);
    sem_init(&shm->non_full, 1, 0);

    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            if (i == 0) chef_donatello(shm);
            if (i == 1) chef_portecelli(shm);
            if (i == 2) customer_nonveg(shm);
            if (i == 3) customer_vegan(shm);
            if (i == 4) customer_hybrid(shm);
            exit(0);
        }
    }

    while (1) {
        sleep(10);
        int v = 0, n = 0;

        for (int i = 0; i < SIZE; i++) {
            if (shm->vegan_tray[i]) v++;
            if (shm->nonvegan_tray[i]) n++;
        }

        printf("\n[STATUS] Vegan tray: %d/10 | Non-Vegan tray: %d/10\n\n", v, n);
        fflush(stdout);
    }

    return 0;
}
