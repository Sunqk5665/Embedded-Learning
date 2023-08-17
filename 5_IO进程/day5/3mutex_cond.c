/*练习：.通过两个线程实现数组倒置，线程一用于循环倒置，线程二用于循环打印。
用互斥锁 + 条件变量实现同步
int a[10] = {0,1,2,3,4,5,6,7,8,9};
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
pthread_mutex_t lock;
pthread_cond_t cond;

void *reverse(void *arg)
{
    int temp;
    while (1)
    {
        sleep(1); //保证print先抢到锁,让其阻塞等待信号
        pthread_mutex_lock(&lock);
        for (int i = 0, j = 9; i < j; i++, j--)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        pthread_cond_signal(&cond);  //产生条件
        pthread_mutex_unlock(&lock); //解锁
    }
    pthread_exit(NULL);
    return NULL;
}
void *print(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        // 阻塞等待条件产生，若没条件，则解锁，条件到来解除阻塞上锁
        pthread_cond_wait(&cond, &lock);
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
    return NULL;
}
int main(int argc, char const *argv[]) //主进程
{
    pthread_t tid1;
    pthread_t tid2;
    if (pthread_mutex_init(&lock, NULL)) //初始化互斥锁
    {
        perror("mutex_init err");
        return -1;
    }
    if (pthread_cond_init(&cond, NULL)) //初始化条件变量
    {
        perror("cond_init err");
        return -1;
    }
    // 创建线程
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
    // 阻塞回收线程
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
