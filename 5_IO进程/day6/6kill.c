#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("start...\n");
    //kill(getpid(),SIGINT);
    //raise(2);//给自己发送信号
    //printf("end...\n");
    //while(1);
    //pause();//挂起信号，直到收到信号被捕捉为止
    return 0;
}
