#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Please iniput %s <src> <dest>\n", argv[0]);
        return -1;
    }
    if (mkfifo("./fifo", 0666) < 0) //创建有名管道
    {
        //处理文件已存在的情况
        if (errno == EEXIST) //EEXTST=17
        {
            printf("file eexist\n");
        }
        else
        {
            perror("mkfifo err");
            return -1;
        }
    }
    //打开管道、源文件、目标文件
    
    int src = open(argv[1], O_RDONLY);
    if (src < 0)
    {
        perror("open src err");
        return -1;
    }
    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest < 0)
    {
        perror("open dest err");
        return -1;
    }

    ssize_t s;
    char buf[32] = {0};

    pid_t pid = fork(); // 创建子进程
    if (pid < 0)
    {
        perror("fork err");
        return -1;
    }
    else if (pid == 0) //子进程从有名管道中读出数据，写到目标文件中
    {
        int fd = open("./fifo", O_RDONLY); //管道设置为只读
        if (fd < 0)
        {
            perror("open fifo err");
            return -1;
        }
        while ((s = read(fd, buf, 32)) != 0)
            write(dest, buf, s);
        printf("child end...\n");
        close(fd);
        exit(0);
    }
    else //父进程从源文件读出数据，写到有名管道中
    {
        int fd = open("./fifo", O_WRONLY); //管道设置为只写
        if (fd < 0)
        {
            perror("open fifo err");
            return -1;
        }
        while ((s = read(src, buf, 32)) != 0)
            write(fd, buf, s);
        printf("parent end...\n");
        close(fd);
        wait(NULL);
    }
    close(src);
    close(dest);
    return 0;
}
