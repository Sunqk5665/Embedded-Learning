//练习：利用文件操作实现ls操作（不含有隐藏文件）
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    //打开目录
    DIR *dir = opendir(argv[1]);
    if(dir == NULL)
    {
        perror("opendir err");
        return -1;
    }
    printf("opendir ok\n");
    //读目录
    struct dirent *d;

    while((d=readdir(dir)) != NULL)
    {
        if(d->d_name[0] != '.') //剔除隐藏文件.and..
            printf("%s ",d->d_name);
    }
    putchar(10);
    
    closedir(dir);
    return 0;
}
