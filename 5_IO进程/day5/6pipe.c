#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd[2] = {0};
    if(pipe(fd)<0)
    {
        perror("pipe error");
        return -1;
    }
    printf("fd[0]:%d  fd[1]:%d\n",fd[0],fd[1]);
    
    char buf1[32] = {"hello world!"};
    char buf2[32] = {0};
    write(fd[1],buf1,32);//往管道写入buf1
    read(fd[0],buf2,32);//从管道读取数据到buf2
    printf("%s\n",buf2);

    close(fd[0]);
    close(fd[1]);
    return 0;
}
