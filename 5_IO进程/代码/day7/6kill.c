#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("start...\n");
    /*1.kill给指定的进程发送指定的信号*/
    // kill(getpid(),SIGINT);
    /*2.raise给自己发送信号*/
    // raise(2);//给自己发送信号
    //printf("end...\n");
    /*3.pause挂起进程，直到捕捉到信号才会返回*/
    pause(); //不占用cpu
    // while(1); //一直轮寻，占用CPU
    return 0;
}
