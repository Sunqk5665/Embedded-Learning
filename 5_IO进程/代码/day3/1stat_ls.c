/*
    实现 ls -l pathname，即打印文件信息，命令行输入./a.out pathname，如下输出格式：
        -rw-rw-r-- 1 hq hq 400 8月   8 10:46 2opendir.c
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    struct stat st;
    if (stat(argv[1], &st) < 0) // 保存文件属性信息到结构体指针类型的st中
    {
        perror("stat err");
        return -1;
    }
    /***获取文件属性（七种:bcd-lsp）***/
    if (S_ISBLK(st.st_mode))
        putchar('b');
    if (S_ISCHR(st.st_mode))
        putchar('c');
    if (S_ISDIR(st.st_mode))
        putchar('d');
    if (S_ISREG(st.st_mode))
        putchar('-');
    if (S_ISLNK(st.st_mode))
        putchar('l');
    if (S_ISSOCK(st.st_mode))
        putchar('s');
    if (S_ISFIFO(st.st_mode))
        putchar('p');

    /***获取文件权限 ****/
    char arr[3] = "rwx";
    for (int i = 0; i < 9; i++)
        (st.st_mode & (0400 >> i)) ? printf("%c", arr[i % 3]) : printf("-");

    printf(" %u", st.st_nlink);                   //文件链接数
    printf(" %s ", getpwuid(st.st_uid->pw_name); //用户名
    printf("%s ", getgrgid(st.st_gid)->gr_name);  //组名
    printf("%ld ", st.st_size);                   //获取文件大小
    printf("%.12s", ctime(&st.st_mtime) + 4);     // 获取文件上次修改时间
                                                  // ctime参数为绝对时间（1970-01-01 00:00:00以来经过的秒数）取地址
    printf(" %s", argv[1]);                       //文件名称
    putchar(10);

    return 0;
}
