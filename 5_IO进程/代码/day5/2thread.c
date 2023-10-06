/*
    练习：通过线程实现数据的交互，主线程循环从终端输入，线程函数将数据循环输出，当输入quit结束程序。
    要点：
        全局变量：线程间可用全局变量通信
        输入输出控制：为防止终端循环打印，可设置标志位进行控制
        quit的处理：终端输入quit后会将'\n'输进去，故要对'\n'进行处理
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>

char buf[32] = {0};
int flag = 0;
void *handler(void *arg)
{
    // char *ch = (char *)arg;
    while (1)
    {
        if (flag == 1)
        {
            if (!strcmp(buf, "quit"))
                break;
            printf("buf:%s\n", buf);
            flag = 0;
        }
    }
    pthread_exit(NULL);
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, handler, NULL) != 0)
    {
        perror("pthread_create err");
        return -1;
    }
    while (1)
    {
        if (flag == 0)
        {
            fgets(buf, 32, stdin);
            if (buf[strlen(buf) - 1] == '\n')
                buf[strlen(buf) - 1] = '\0';
            flag = 1;
            if (!strcmp(buf, "quit"))
                break;
        }
    }
    pthread_join(tid, NULL); // 阻塞回收线程
    return 0;
}
