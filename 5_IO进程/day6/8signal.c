#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("hello world!\n");
}

int main(int argc, char const *argv[])
{
    //1.忽略信号
    signal(2,SIG_IGN); //终端用ctrl+\退出
    // //2.缺省操作
    // signal(SIGINT,SIG_DFL);

    // //3.捕捉信号
    // signal(2,handler);//捕捉结束进程信号
    // signal(SIGTSTP,handler);//捕捉暂停信号（ctrl+Z）

    pause();//阻塞
    return 0;
}
