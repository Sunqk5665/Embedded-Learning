#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    if(sig == 2)
        printf("hello world!\n");
    else
        printf("nonono\n");
}

int main(int argc, char const *argv[])
{
    // //1.忽略信号
    // signal(2,SIG_IGN); //ctrl+\退出
    // //2.缺省操作
    // signal(SIGINT,SIG_DFL);

    //3.捕捉信号
    signal(2,handler);//捕捉终止（ctrl+C）信号
    signal(SIGTSTP,handler);//捕捉暂停（ctrl+Z）信号

    pause();
    return 0;
}
