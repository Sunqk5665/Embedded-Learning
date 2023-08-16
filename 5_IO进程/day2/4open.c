/*
r :只读，文件不存在报错，存在文件流定位到文件开头 O_RDONLY
r+:可读可写，文件不存在报错，存在文件流定位到文件开头 O_RDWR
w :只写，文件不存在创建，存在清空  O_WRONLY | O_CREAT | O_TRUNC,0666
w+:可读可写，文件不存在创建，存在清空，O_RDWR | O_CREAT | O_TRUNC,0666
a :追加，文件不存在创建，存在追加，文件流定位到文件结尾 O_APPEND | O_RDONLY | O_CREAT,0666
a+:读和追加，文件不存在创建，存在追加，读文件流定位到文件开头，写文件流定位到文件末尾 O_RDWR | O_APPEND | O_CREAT,0666
*/



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

    //r 只读，当文件不存在时报错，文件流定位到文件开头
    int fd = open("a.txt",O_RDONLY);
    if(fd < 0)
    {
        perror("open err");
        return -1;
    }
    // //r+
    // int fd = open("./a.txt",O_RDWR);
    // if(fd < 0)
    // {
    //     perror("open err");
    //     return -1;
    // }

    // //w 只写，文件不存在创建，存在清空
    // int fd = open("a.txt",O_WRONLY | O_CREAT | O_TRUNC,0666);
    // if(fd < 0)
    // {
    //     perror("open err");
    //     return -1;
    // }

    // //w+
    // int fd = open("a.txt",O_RDWR | O_CREAT | O_TRUNC,0666);
    // if(fd < 0)
    // {
    //     perror("open err");
    //     return -1;
    // }

    // //a 追加(在末尾写),文件不存在创建，存在追加，文件流定位到文件末尾
    // int fd = open("a.txt",O_APPEND | O_RDONLY | O_CREAT,0666);
    // if(fd < 0)
    // {
    //     perror("open err");
    //     return -1;
    // }

    // //a+ 读和追加，文件不存在创建，存在追加，读文件流定位到文件开头，写文件流定位到文件末尾
    // int fd = open("a.txt",O_RDWR | O_APPEND | O_CREAT,0666);
    // if(fd < 0)
    // {
    //     perror("open err");
    //     return -1;
    // }

    clsoe(fd);

    return 0;
}
