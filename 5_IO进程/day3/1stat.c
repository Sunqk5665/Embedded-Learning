#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
int main(int argc, char const *argv[])
{
    struct stat st;
    if(stat(argv[1],&st)<0) //保存文件属性信息到结构体指针类型的st中
    {
        perror("stat error");
        return -1;
    }

/*****获取文件属性 方法一**************/
    if ((st.st_mode & S_IFMT) == S_IFREG) {
        putchar('-');
    }
    if ((st.st_mode & S_IFMT) == S_IFBLK) {
        putchar('b');
    }
    if ((st.st_mode & S_IFMT) == S_IFCHR) {
        putchar('c');
    }
    if ((st.st_mode & S_IFMT) == S_IFDIR) {
        putchar('d');
    }
    if ((st.st_mode & S_IFMT) == S_IFLNK) {
        putchar('l');
    }
    if ((st.st_mode & S_IFMT) == S_IFSOCK) {
        putchar('s');
    }
    if ((st.st_mode & S_IFMT) == S_IFIFO) {
        putchar('p');
    }
    putchar(10);
// 或者用switch
switch (st.st_mode & S_IFMT)
{
case S_IFREG:
    putchar('-');break;
case S_IFBLK:
    putchar('b');break;
case S_IFCHR:
    putchar('c');break;
case S_IFDIR:
    putchar('d');break;
case S_IFLNK:
    putchar('l');break;
case S_IFMT:
    putchar('s');break;
case S_IFIFO:
    putchar('p');break;
default:
    break;
}

/*****获取文件属性 方法二**************/
    if (S_ISBLK(st.st_mode)) {
        putchar('b');
    }
    if (S_ISCHR(st.st_mode)) {
        putchar('c');
    }
    if (S_ISDIR(st.st_mode)) {
        putchar('d');
    }
    if (S_ISREG(st.st_mode)) {
        putchar('-');
    }
    if (S_ISLNK(st.st_mode)) {
        putchar('l');
    }
    if (S_ISSOCK(st.st_mode)) {
        putchar('s');
    }
    if (S_ISFIFO(st.st_mode)) {
        putchar('p');
    }


/******获取文件权限 **********/
    if(st.st_mode & 0400)
        putchar('r');
    else
        putchar('-');
    if(st.st_mode & 0200)
        putchar('w');
    else
        putchar('-');
    if(st.st_mode & 0100)
        putchar('x');
    else
        putchar('-');

    if(st.st_mode & 0040)
        putchar('r');
    else
        putchar('-');
    if(st.st_mode & 0020)
        putchar('w');
    else
        putchar('-');
    if(st.st_mode & 0010)
        putchar('x');
    else
        putchar('-');
    
    if(st.st_mode & 0004)
        putchar('r');
    else
        putchar('-');
    if(st.st_mode & 0002)
        putchar('w');
    else
        putchar('-');
    if(st.st_mode & 0001)
        putchar('x');
    else
        putchar('-');

    
/******获取文件权限 方法二（简单）**********/
    char arr[3] = "rwx";
    for(int i=0;i<9;i++)    
        (st.st_mode&(0400>>i))?printf("%c",arr[i%3]):printf("-");
    printf(" %u",st.st_nlink); //文件链接数
    printf(" %s ",getpwuid(st.st_gid)->pw_name); //用户名
    printf("%s ",getgrgid(st.st_gid)->gr_name);  //组名
    printf("%ld ",st.st_size);//获取文件大小
    printf("%.12s",ctime(&st.st_mtime)+4); // 获取文件上次修改时间，12：字符串位宽，+4：字符串首地址移动
                        // ctime参数为绝对时间（1970-01-01 00:00:00以来经过的秒数）取地址
    printf(" %s",argv[1]); //文件名称
    putchar(10);
    return 0;
}