#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg)
{
    pthread_t tid = pthread_self(); 
    printf("Thread với ID %lu đang chạy!\n", tid);
    return NULL;
}

int main()
{
    pthread_t t1, t2;
//tao 2 luong
    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Luồng chính kết thúc!\n");
    return 0;
}
