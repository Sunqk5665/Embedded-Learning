#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd[2] = {0};
    if (pipe(fd) < 0)
    {
        perror("pipe error");
        return -1;
    }
    printf("fd[0]:%d  fd[1]:%d\n", fd[0], fd[1]);

    char buf1[32] = {"hello world!"};
    char buf2[32] = {0};
    // write(fd[1],buf1,strlen(buf1)); //往管道写入buf1
    // ssize_t s = read(fd[0],buf2,32);  //从管道读取数据到buf2
    // printf("%s %d\n",buf2,s);
    // close(fd[0]);
    // close(fd[1]);
#if 0
    // 1.管道中无数据，读阻塞
    read(fd[0], buf2, 32);
#endif
#if 0
    // 2.将写端关闭，读操作会立即返回
    close(fd[1]);
    read(fd[0],buf2,32);
#endif
#if 1
    //3.当无名管道中写满数据64k，写阻塞
    char buf[65536] = {0};
    write(fd[1], buf, 65536);
    printf("full\n");
    write(fd[1], "a", 1);
    printf("write a ok\n");
    //至少读出4k的空间，才能继续写
    read(fd[0], buf, 4095);
    write(fd[1], 'a', 1);
    printf("write 'a' ok\n");
#endif
#if 1
    // 4,将读端关闭，继续写
    close(fd[0]);
    write(fd[1], "a", 1);
    printf("ok...\n");
#endif
    // close(fd[0]);
    // close(fd[1]);
    return 0;
}
