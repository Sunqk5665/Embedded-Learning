//实现cp功能 
#include <stdio.h>
int main(int argc, char const *argv[])
{
    if(argc != 3)//判断输入格式是否正确
    {
        printf("Please input:%s <srcfile> <destfile>",argv[0]);
        return -1;
    }
    FILE *src = fopen(argv[1],"r");
    FILE *dest = fopen(argv[2],"w+");
    if(NULL == src)
    {
        perror("fopen src err");
        return -1;
    }
    if(NULL == dest)
    {
        perror("fopen dest err");
        return -1;
    }
    char buf[50] = {0};
/*****（方法一）************/
    // while(1)
    // {
    //     if(fgets(buf,50,src) != NULL)
    //         fputs(buf,dest);
    //     else
    //         break;
    // }
/******（方法二）***********/
    while(fgets(buf,50,src) != NULL)
        fputs(buf,dest);
/*************************/
    //关闭文件
    fclose(src);
    fclose(dest);
    return 0;
}
