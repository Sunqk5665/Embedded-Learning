//创建守护进程实现往日志文件中循环写入hello,间隔时间为1秒
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    //1.创建父子进程
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork err");
        return -1;
    }
    else if(pid == 0)//子进程进入
    {
        int fd = open("/tmp/c.log",O_WRONLY|O_CREAT|O_APPEND,0666);
        if(fd < 0)
        {
            perror("open err");
            return -1;
        }
        setsid();//2.在子进程中创建新会话，让子进程成为会话组组长
        chdir("/");//3.改变运行目录为根目录
        umask(0);//4.重设文件掩码
        for(int i = 0; i<3; i++)
        {
            close(i);//5.关闭文件描述符->0 1 2
        }
        while(1)
        {
            sleep(1);
            write(fd,"hello",5);  
        }
    }
    else
    {
        exit(0); //1.父进程退出
    }
    return 0;
}
