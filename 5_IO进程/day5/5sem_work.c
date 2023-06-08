/*练习：.通过两个线程实现数组倒置，线程一用于循环倒置，线程二用于循环打印。
用互斥锁实现同步
int a[10] = {0,1,2,3,4,5,6,7,8,9};
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
sem_t sem;


void *reverse(void *arg)
{
    int temp;
    while(1)
    {
        for (int i = 0, j = 9; i < j; i++, j--)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        sem_post(&sem);
    }
    pthread_exit(NULL);
    return NULL;
}
void *print(void *arg)
{
    while(1)
    {
        //sleep(1);
        sem_wait(&sem);
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[]) //主进程
{
    pthread_t tid1;
    pthread_t tid2;


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
    
    if(sem_init(&sem,0,0)<0)
    {
        perror("sem_init err\n");
        return -1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
