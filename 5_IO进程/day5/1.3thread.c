#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *testThread(void *arg)
{
    printf("arg=%d\n",(int)*arg); //会报错
    // printf("arg=%d\n",*(int *)arg);
    
    pthread_exit(NULL);
}
int main(int argc, char const *argv[])
{
    pthread_t tid;
    int arg = 5;
    //创建线程
    if(pthread_create(&tid, NULL, testThread, (void *)&arg) !=0 )//创建成功返回0
    {
        perror("pthread_creatr err");
        return -1;
    }
    sleep(1);
    return 0;
}
