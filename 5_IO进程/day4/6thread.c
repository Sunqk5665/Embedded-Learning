#include <stdio.h>
#include <pthread.h>

void *handler(void *arg)
{
    printf("in pthread\n");
    pthread_exit(NULL); //线程退出
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    //创建线程
    if(pthread_create(&tid, NULL, handler, NULL) !=0 )
    {
        perror("pthread_creatr err");
        return -1;
    }
    printf("in main\n");
    //while(1);
    pthread_join(tid,NULL); //回收线程
    return 0;
}
