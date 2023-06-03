#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    } 
    //（方法一）
    // int hang = 0;
    // char buf[50];
    // while (1)
    // {
    //     if(fgets(buf,50,fp) != NULL)
    //         hang++;
    //     else
    //         break;
    // }
    // printf("%d\n",hang);

    //（方法二）
    char buf[32] = {0};
    int len = 0;
    while(fgets(buf,32,fp) != NULL)
    {//由于文件中某一行不一定能够读完，所以要判断读入字符所形成的字符串末尾\0前一个字符是否是\n
        if(buf[strlen(buf) - 1] == '\n')
            len++;
    }
    printf("%d %s\n",len,argv[1]);
    fclose(fp);
    return 0;
}
