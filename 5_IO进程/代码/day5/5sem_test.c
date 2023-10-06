/*
    练习：使用信号量实现同步，即通过线程实现数据的交互，主线程循环从终端输入，
        线程函数将数据循环输出，当输入quit结束程序。
    要点：
        信号量初值的设定：初始化信号量为0，是为了让打印线程开始申请不到资源
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h> 

char buf[32] = {0};
sem_t sem;

void *handler(void *arg) //线程函数循环输出
{
    while (1)
    {
        sem_wait(&sem); //P  申请资源
        if(strcmp(buf,"quit")==0)
        {
            pthread_exit(NULL);
        }
        printf("buf:%s\n",buf);
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t tid; //创建线程
    if(pthread_create(&tid,NULL,handler,NULL) != 0)
    {
        perror("pthread_create err");
        return -1;
    }
    //初始化信号量为0，是为了让打印线程开始申请不到资源
    if(sem_init(&sem,0,0)<0)
    {
        perror("sem_init err\n");
        return -1;
    }
    while(1)
    {
        // scanf("%s",buf);
        fgets(buf,32,stdin);
        if(buf[strlen(buf)-1]=='\n')
            buf[strlen(buf)-1] = '\0';
        sem_post(&sem); // V  释放资源
        if(strcmp(buf,"quit")==0)
        {
            break;
        }
    }
    pthread_join(tid, NULL);
    sem_destroy(&sem);
    return 0;
}
