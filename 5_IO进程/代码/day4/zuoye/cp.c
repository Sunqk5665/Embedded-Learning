//通过父子进程完成对文件的拷贝(cp)，父进程从文件开始到文件
//的一半开始拷贝，子进程从文件的一半到文件末尾。要求：文件IO cp src dest
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Please input:%s <srcfile> <destfile>\n", argv[0]);
        return -1;
    }
    int src = open(argv[1], O_RDONLY);
    if (src < 0)
    {
        perror("srcfile open err");
        return -1;
    }
    int dest = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (dest < 0)
    {
        perror("destfile open err");
        return -1;
    }
    off_t half = lseek(src, 0, SEEK_END) / 2; // 文件长度的一半
    int flag = 0;                             // 控制下面父子进程执行顺序，让父进程先执行
    ssize_t s;
    char buf[32] = {0};

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork err");
        return -1;
    }
    else if (pid == 0) // 子进程 复制源文件后半部分
    {
        while (flag == 1) // 父进程已复制完毕，子进程可以执行
        {
            lseek(src, half, SEEK_SET);
            lseek(dest, half, SEEK_SET);
            while ((s = read(src, buf, 32)) != 0)
                write(dest, buf, s);
        }
    }
    else // 父进程 复制源文件前半部分（先执行）
    {
        lseek(src, 0, SEEK_SET);
        lseek(dest, 0, SEEK_SET);
        int n = half;
        if (n < 32)
        {
            read(src, buf, n);
            write(dest, buf, n);
            flag = 1;
            wait(NULL);
        }
        else
        {
            while ((s = read(src, buf, 32)) != 0)
            {
                write(dest, buf, s);
                n = n - s;
                if (n < 32)
                {
                    read(src, buf, n);
                    write(dest, buf, n);
                    flag = 1;
                    wait(NULL);
                }
            }
        }
    }
    close(src);
    close(dest);
    return 0;
}
