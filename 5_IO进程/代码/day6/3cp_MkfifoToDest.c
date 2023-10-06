#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        printf("Please input %s <des>\n",argv[0]);
        return -1;
    }
    if(mkfifo("./fifo",0666) < 0)//创建有名管道
    {
        //处理文件已存在的情况
        if(errno == EEXIST)//EEXTST=17
        {
            printf("file eexist\n");
        }
        else
        {
            perror("mkfifo err");
            return -1;
        }
    }
    //打开管道和目标文件
    int fd = open("./fifo",O_RDONLY);
    //此处一定不要用可读可写的方式打开
    //若以可读可写的方式打开，管道中无数据则读阻塞
    if(fd<0)
    {
        perror("open fifo err");
        return -1;
    }
    int dest = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(fd<0)
    {
        perror("open dest err");
        return -1;
    }
    //循环读管道，写目标文件
    ssize_t s;
    char buf[32] = {0};
    while ((s=read(fd,buf,32)) != 0)
        write(dest,buf,s);
    close(fd);
    close(dest);
    return 0;
}
