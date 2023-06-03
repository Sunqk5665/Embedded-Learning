#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
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
    return 0;
}
 