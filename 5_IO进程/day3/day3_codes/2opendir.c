#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    //打开目录
    DIR *dir = opendir(".");
    if(dir == NULL)
    {
        perror("opendir err");
        return -1;
    }
    printf("opendir ok\n");
    
    struct dirent *d;
    d = readdir(dir);
    printf("name:%s\n",d->d_name);
    //关闭文件
    closedir(dir);

    return 0;
}
