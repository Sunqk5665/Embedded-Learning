#include <stdio.h>
int main(int argc, char const *argv[])
{//a.txt内的文件内容为world
    FILE *fp = fopen("a.txt","r+");
    if(fp == NULL)
    {
        perror("fopen err");
        return -1;
    }
    char ch = fgetc(fp);
    printf("%c\n",ch);
    fputc('w',fp);
    fgetc(fp);//l
    fgetc(fp);//l
    fgetc(fp);//o
    fgetc(fp);//读文件结束符
    //判断当前位置之后是否还存在字符
    if(feof(fp))
    {
        printf("file end...\n");
        return -1;
    }
    if(ferror(fp))
    {
        printf("file err\n");
        return -1;
    }

#if 0
    for(int i = 0;i<3;i++)
    {
        printf("%c\n",fgetc(fp));
    }


    FILE *fp = fopen("a.txt","r+");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    }
    printf("fopen success\n");

    char ch = fgetc(fp);
    printf("%c\n",ch);
    fputc('w',fp);
    //若以只读形式打开文件，则会报错
    if(ferror(fp))
        printf("err\n");
    
    fgetc(fp);
    fgetc(fp);
    fgetc(fp);
    printf("%c\n",fgetc(fp));
    printf("%c\n",fgetc(fp));
    if(feof(fp))  //到达文件末尾返回非零
        printf("end...\n");
    
    fclose(fp);
#endif
    return 0;
}
