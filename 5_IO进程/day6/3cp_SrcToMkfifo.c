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
        printf("Please input %s <src>\n",argv[0]);
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
    //打开管道和源文件
    int fd = open("./fifo",O_WRONLY);
    if(fd<0)
    {
        perror("open fifo err");
        return -1;
    }
    int src = open(argv[1],O_RDONLY);
    if(fd<0)
    {
        perror("open src err");
        return -1;
    }

    ssize_t s;
    char buf[32] = {0};
    while ((s=read(src,buf,32)) != 0)
    {
        write(fd,buf,s);
    }
    close(fd);
    close(src);
    return 0;
}
