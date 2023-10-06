#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if(mkfifo("./fifo",0666) < 0)//创建有名管道
    {//处理错误情况
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

        // if(errno != 17)
        // {
        //     perror("mkfifo err");
        //     return -1;
        // }
    }
    printf("mkfifo success\n");

    char buf[32]={0};
    int fd = open("fifo",O_RDWR);//以读写方式打开管道
    if(fd < 0)
    {
        perror("open fifo err");
        return -1;
    }
    write(fd,"hello",5);
    // while(1);//写完停止，查看管道文件大小为0
    read(fd,buf,32);
    printf("buf:%s\n",buf);

    close(fd);

    return 0;
}
