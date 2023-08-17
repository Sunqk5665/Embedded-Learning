#include <stdio.h>
#include <pthread.h>
#include <string.h>

char buf[32] = {0};
int flag = 0;
void *handler(void *arg)//线程函数循环输出
{
    while (1)
    {
        if(flag == 1)
        {
            if(strcmp(buf,"quit")==0)
            {
                pthread_exit(NULL);
            }
            printf("%s\n",buf);
            flag = 0;
        }
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t tid;
    if(pthread_create(&tid,NULL,handler,NULL) != 0)
    {
        perror("pthread_create err");
        return -1;
    }
    while(1)
    {
        if(flag==0)
        {
            scanf("%s",buf);
            getchar();
            flag = 1;
        }
        if(strcmp(buf,"quit")==0)
        {
            break;
        }
    }
    pthread_join(tid, NULL);
    return 0;
}
