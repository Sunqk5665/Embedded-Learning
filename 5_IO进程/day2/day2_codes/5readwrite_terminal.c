#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buf[32] = {0};
/****终端读入写出********/
    read(0,buf,32);
    write(1,buf,32);
/**********************/

    //关闭文件
    //close(fd);
    return 0;
}
