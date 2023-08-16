#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fd = open("a.txt", O_RDWR | O_TRUNC | O_CREAT, 0666);
    if (fd < 0)
    {
        perror("open err");
        return -1;
    }
    printf("fd:%d\n", fd);

    write(fd, "hello", 5);
    char buf[32] = {0};

    //将文件指针定位到开始位置
    lseek(fd, 0, SEEK_SET);

    read(fd, buf, 32);
    printf("buf:%s\n", buf);
    close(fd);

#if 0
    int fd = open("b.txt",O_RDWR);
    if(fd < 0)
    {
        perror("open err");
        return -1;
    }
    printf("fd:%d\n",fd);

    char buf[32] = {0};
    read(fd,buf,32); //从fd读出32长度数据到buf中
    printf("buf:%s\n",buf);
    write(fd,"23041",sizeof("23041")-1); //读出数据到fd中

    //关闭文件
    close(fd);
#endif
    return 0;
}
