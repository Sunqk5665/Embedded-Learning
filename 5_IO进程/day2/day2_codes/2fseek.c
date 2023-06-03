#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp = fopen("a.txt","w+");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    }
    printf("fopen success\n");

    fputs("hello world",fp);
    fseek(fp,-5,SEEK_END);
    fputc('a',fp);
    fseek(fp,0,SEEK_SET);
    fputs("ni hao",fp);
    /******获取文件长度**********/
    fseek(fp,0,SEEK_END);
    long len = ftell(fp);
    /**************************/
    printf("len = %ld\n",len);
    return 0;
}