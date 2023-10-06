#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
pthread_mutex_t lock;

void *reverse(void *arg)
{
    int temp;
    while (1)
    {
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 10/2; i++)
        {
            temp = a[i];
            a[i] = a[9-i];
            a[9-i] = temp;
        }
        pthread_mutex_unlock(&lock);
    }
}
void *print(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, NULL, reverse, NULL) != 0)
    {
        perror("pthread_create tid1 error");
        return -1;
    }
    if (pthread_create(&tid2, NULL, print, NULL) != 0)
    {
        perror("pthread_create tid2 error");
        return -1;
    }

    if (pthread_mutex_init(&lock, NULL))
    {
        perror("mutex err");
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}
