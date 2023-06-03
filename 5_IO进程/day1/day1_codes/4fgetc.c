#include <stdio.h>
int main(int argc, char const *argv[])
{//a.txt内的文件内容为world
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
    return 0;
}
