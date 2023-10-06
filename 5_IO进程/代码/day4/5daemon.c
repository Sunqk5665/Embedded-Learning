/*创建守护进程*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    //1.1创建父子进程
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork err");
        return -1;
    }
    else if(pid == 0) //子进程进入
    {
        setsid(); //2.在子进程中创建新会话，让子进程成为会话组组长
        chdir("/"); //3.改变运行目录为根目录
        umask(0); //4.重设文件掩码
        for(int i = 0; i<3; i++)
        {
            close(i); //5.关闭文件描述符->0 1 2
        }
        while(1);
    }
    else
    {
        exit(0);  //1.2父进程退出
    }
    return 0;
}
