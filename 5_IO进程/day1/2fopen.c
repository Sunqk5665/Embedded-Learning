#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *fp = fopen("a.txt","w");
    if(fp == NULL)
    {
        perror("fopen err");
        return -1;
    }
    //关闭文件流
    fclose(fp);
    return 0;
}
