/*
练习一：
用信号的知识实现司机和售票员问题。
1）售票员捕捉SIGINT（代表开车）信号，向司机发送SIGUSR1信号，司机打印（let's gogogo）
2）售票员捕捉SIGQUIT（代表停车）信号，向司机发送SIGUSR2信号，司机打印（stop the bus）
3）司机捕捉SIGTSTP（代表到达终点站）信号，向售票员发送SIGUSR1信号，售票员打印（please get off the bus）
4）司机等待售票员下车，之后司机再下车。
*/
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig);
void go(int sig);
void stop(int sig);
void off(int sig);

pid_t pid;
int main(int argc, char const *argv[])
{
    //创建子进程，子进程作为售票员，父进程作为司机
    pid = fork();
    if(pid < 0)
    {
        perror("fork pid_seller error");
        return -1;
    }
    else if(pid == 0)//子进程：售票员
    {     
        signal(SIGINT,handler); //1）a.售票员捕捉SIGINT（代表开车）信号
        signal(SIGQUIT,handler);//2）a.售票员捕捉SIGQUIT（代表停车）信号

        signal(SIGUSR1,off);//3）c.售票员打印（please get off the bus）
        
        signal(SIGTSTP,SIG_IGN);//子进程（售票员）忽略SIGTSTP

        pause();
        while(1);
    }
    else//父进程：司机
    {
        signal(SIGUSR1,go);  //1）c.司机打印（let's gogogo）
        signal(SIGUSR2,stop);//2）c.司机打印（stop the bus）

        signal(SIGTSTP,handler);//3）a.司机捕捉SIGTSTP（代表到达终点站）信号

        signal(SIGINT,SIG_IGN); //父进程（司机）忽略SIGINT
        signal(SIGQUIT,SIG_IGN); //父进程（司机）忽略SIGQUIT

        pause();
        while(1);
        wait(NULL);
    }
    return 0;
}

void handler(int sig)
{
    if(sig == SIGINT)  //1）b.售票员向司机发送SIGUSR1信号
    {
        kill(getppid(),SIGUSR1);
    }
    if(sig == SIGQUIT) //2）b.售票员向司机发送SIGUSR2信号
    {
        kill(getppid(),SIGUSR2);
    }
    if(sig == SIGTSTP)//3）b.司机向售票员发送SIGUSR1信号
    {
        kill(pid,SIGUSR1);
    }
}
void go(int sig)
{
    printf("司机：let's gogogo\n");
}
void stop(int sig)
{
    printf("司机：stop the bus\n");
}
void off(int sig)
{
    printf("售票员：please get off the bus\n");
}
