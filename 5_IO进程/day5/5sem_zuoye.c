#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

char buf[32] = {0};
sem_t sem1;
//sem_t sem2;

void *handler(void *arg)//线程函数循环输出
{
    while (1)
    {
        sem_wait(&sem1); //P  申请资源
        if(strcmp(buf,"quit")==0)
        {
            pthread_exit(NULL);
        }
        printf("buf:%s\n",buf);
        //sem_post(&sem2);
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

    if(sem_init(&sem1,0,0)<0)
    {
        perror("sem_init err\n");
        return -1;
    }
    // if(sem_init(&sem2,0,1)<0)
    // {
    //     perror("sem_init err\n");
    //     return -1;
    // }

    while(1)
    {
        //sem_wait(&sem2);
        scanf("%s",buf);
        //getchar();
        // fgets(buf,32,stdin);
        // if(buf[strlen(buf)-1]=='\n')
        //     buf[strlen(buf)-1] = '\0';
        sem_post(&sem1); // V  释放资源
        if(strcmp(buf,"quit")==0)
        {
            break;
        }
    }
    pthread_join(tid, NULL);
    sem_destroy(&sem1);
    //sem_destroy(&sem2);
    return 0;
}
