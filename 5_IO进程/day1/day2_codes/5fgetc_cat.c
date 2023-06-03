//练习：通过fgetc实现cat功能
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    }
    printf("fopen success\n");
    // //方法一
    // char ch;
    // while (1)
    // {
    //     ch = fgetc(fp);
    //     if(feof(fp))
    //         break;
    //     fputc(ch,stdout);
    // }
    //方法二
    char ch = fgetc(fp);
    while(!feof(fp))
    {
        // ch = fgetc(fp);
        // fputc(ch,stdout);//这样打印最后会输出一个乱码（实际是文件末尾的EOF）
        fputc(ch,stdout);
        ch = fgetc(fp);
    }

    fclose(fp);
    return 0;
}