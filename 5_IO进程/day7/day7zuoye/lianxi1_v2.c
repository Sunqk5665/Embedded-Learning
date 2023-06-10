/*
练习一：
用信号的知识实现司机和售票员问题。
1）售票员捕捉SIGINT（代表开车）信号，向司机发送SIGUSR1信号，司机打印（let's gogogo）
2）售票员捕捉SIGQUIT（代表停车）信号，向司机发送SIGUSR2信号，司机打印（stop the bus）
3）司机捕捉SIGTSTP（代表到达终点站）信号，向售票员发送SIGUSR1信号，售票员打印（please get off the bus）
4）司机等待售票员下车，之后司机再下车。
*/
/*
分析：各个进程要捕捉和忽略的信号
售票员(子进程)：
    捕捉：SIGINT,SIGQUIT,SIGUSR1
    忽略：SIGTSTP
司机(父进程)：
    捕捉：SIGTSTP,SIGUSR1,SIGUSR2
    忽略：SIGINT,SIGQUIT
*/
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t pid; //pid设置为为全局变量

void saller(int arg)
{
    if(arg == SIGINT)
        kill(getppid(),SIGUSR1);
    if(arg == SIGQUIT)
        kill(getppid(),SIGUSR2);
    if(arg == SIGUSR1)
    {
        printf("售票员：please get off the bus\n");
        exit(0);
    }
}
void driver(int arg)
{
    if(arg == SIGUSR1)
        printf("司机：let's gogogo\n");
    if(arg == SIGUSR2)
        printf("司机：stop the bus\n");
    if(arg == SIGTSTP)
    {
        kill(pid,SIGUSR1);//要注意pid要为全局变量
        wait(NULL);//阻塞回收子进程资源
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    pid = fork();//创建父子进程
    if(pid < 0)
    {
        perror("fork err");
        return -1;
    }
    else if(pid == 0) //售票员(子进程)
    {
        //子进程要捕捉的信号
        signal(SIGINT,saller);
        signal(SIGQUIT,saller);
        signal(SIGUSR1,saller);

        //子进程要忽略的信号
        signal(SIGTSTP,SIG_IGN);
    }
    else //司机(父进程)
    {
        //父进程要捕捉的信号
        signal(SIGTSTP,driver);
        signal(SIGUSR1,driver);
        signal(SIGUSR2,driver);

        //父进程要忽略的信号
        signal(SIGINT,SIG_IGN);
        signal(SIGQUIT,SIG_IGN);
    }
    while(1)
        pause();//这样比只有一个while占用CPU更少
    return 0;
}


