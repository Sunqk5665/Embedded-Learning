#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    FILE *fp = fopen("a.txt","r+");
    if(fp == NULL)
    {
        perror("fopen err");
        return -1;
    }
    char buf[32] = {0};
    fgets(buf,32,fp);  //buf:hello\n\0
    fputs(buf,stdout);
    fputs("23061",fp); //"23061"输入到文件中
    fgets(buf,32,fp);  //buf:\n\0,(因为23061替换掉world之后，'1后面有一个'\n')
    fputs(buf,stdout);

#if 0
//
    // char buf[32] = {0};
    // fgets(buf,32,stdin);
    // fputs(buf,stdout);
    // printf("buf:%s",buf);

//针对文件
    FILE *fp = fopen("a.txt","r");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    }
    printf("fopen success\n");

    char buf[5] = {0};
    fgets(buf,5,fp);
    fputs(buf,stdout);
    printf("buf:%s,%d\n",buf,strlen(buf));

    fclose(fp);
#endif
    fclose(fp);
    return 0;
}
 