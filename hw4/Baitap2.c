#include <stdio.h>
#include <pthread.h>

long long counter = 0;
pthread_mutex_t lock;

void* add_func(void* arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t t[3];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, add_func, NULL);

    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    pthread_mutex_destroy(&lock);

    printf("Giá trị cuối cùng counter = %lld\n", counter);
    return 0;
}
