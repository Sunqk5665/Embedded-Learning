/*
测试文件描述符最大值
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fd;
    while (1)
    {
        fd = open("a.txt", O_RDONLY);
        if (fd < 0)
            break;
        printf("%d ", fd);
    }//最大值为1023,因此新打开的文件描述符最多有1024-3=1021个

    return 0;
}
