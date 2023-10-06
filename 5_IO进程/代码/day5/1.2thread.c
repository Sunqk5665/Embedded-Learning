#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *handler(void *arg)
{
    printf("in pthread\n");
    // sleep(1);
    // while(1);   
    // pthread_exit(NULL); //线程退出
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    //创建线程
    if(pthread_create(&tid, NULL, handler, NULL) !=0 )//创建成功返回0
    {
        perror("pthread_creatr err");
        return -1;
    }
    printf("in main\n");
    pthread_join(tid,NULL); // 阻塞回收线程
    // pthread_detach(tid);    // 不阻塞，让线程结束时自动回收线程资源，让线程和主线程分离
    return 0;
}
