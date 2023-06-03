#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        printf("Please input:%s <file1> <file2>\n",argv[0]);
        return -1;
    }
    int src = open(argv[1],O_RDONLY);
    if(src < 0)
    {
        perror("open src error");
        return -1;
    }
    int dest = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0666);
    if(dest < 0)
    {
        perror("open src error");
        return -1;
    }
    char buf[32];
    ssize_t s;
    //寻循环读源文件 写目标文件
    while((s=read(src,buf,32)) != 0)
        write(dest,buf,s);
    //关闭文件
    close(src);
    close(dest);

    return 0;
}
