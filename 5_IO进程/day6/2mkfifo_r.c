#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
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
    printf("mkfifo success\n");

    char buf[32]={0};
    ssize_t s = 0;
    int fd = open("fifo",O_RDONLY); //以只读打开管道
    if(fd < 0)
    {
        perror("open fifo err");
        return -1;
    }
    printf("#####\n");
    
    s = read(fd,buf,32);
    printf("buf:%s readSize:%d\n",buf,s);
    printf("read end...\n");

    close(fd);

    return 0;
}
