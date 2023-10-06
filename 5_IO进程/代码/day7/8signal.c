#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    if (sig == SIGINT)
        printf("You pressed ctrl + c!\n");
    else if (sig == SIGTSTP)
        printf("You pressed ctrl + z!\n");
    else if (sig == SIGQUIT)
        printf("You pressed ctrl + \\!\n");
    else
        printf("end...\n");
}

int main(int argc, char const *argv[])
{
    /*1.忽略信号*/
    // signal(2,SIG_IGN); //ctrl+c被忽略，终端用ctrl+\退出

    /*2.缺省（默认）操作*/
    // signal(SIGINT,SIG_DFL);

    /*3.捕捉信号*/
    signal(2, handler);       //捕捉结束进程信号(ctrl+C)
    signal(SIGTSTP, handler); //捕捉暂停信号（ctrl+Z）
    signal(SIGQUIT,handler);  //捕捉推出信号（ctrl+Q）

    //挂起进程，直到捕捉到信号才会返回
    pause();
    return 0;
}
