#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *handler(void *arg)
{
    printf("in pthread\n");
}

int main(int argc, char const *argv[])
{
    // 程序一执行便会创建一个线程，即主线程
    pthread_t tid;
    //创建线程（和主线程并列）
    if(pthread_create(&tid, NULL, handler, NULL) !=0 )//创建成功返回0
    {
        perror("pthread_creatr err");
        return -1;
    }
    printf("in main\n");
    sleep(1);
    // while(1);
    //return 0;
}
