#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int data;
int data_ready = 0;

pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer(void* arg)
{
    for (int i = 0; i < 10; i++)
    {
        int value = rand() % 100;

        pthread_mutex_lock(&mutex);
        data = value;
        data_ready = 1;

        printf("[Producer] Tạo data = %d\n", value);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* arg)
{
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);

        while (data_ready == 0)
            pthread_cond_wait(&cond, &mutex);

        printf("[Consumer] Nhận data = %d\n", data);

        data_ready = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t p, c;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
