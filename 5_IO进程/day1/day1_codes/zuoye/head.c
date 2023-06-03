//实现 head -n 文件名   ./a.out -3 filename
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    if(srgc != 3)//判断输入格式是否正确
    {
        printf("Please input:%s -n <filename>",argv[0]);
    }
    FILE *fp = fopen(argv[2],"r");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    }
    printf("fopen success\n");
    //获取要输出几行
    //int num = -atoi(argv[1]); // 行数转换
    int num = atoi(argv[1]+1);  // str+1表示舍去字符串str前面1个字符的意思
    char buf[50] = {0};
    
/********方法一******************/
    //int len = 1;
    ////读取前n行
    // while(1)
    // {
    //     if(fgets(buf,50,fp)!=NULL && len<=num)
    //     {
    //         len++;
    //         fputs(buf,stdout);
    //     }
    //     else
    //         break;
    // }
/********方法二******************/
    int len = 0;
    //读取前n行
    while (fgets(buf,50,fp) != NULL)
    {
        if(buf[strlen(buf)-1] == '\n')
            len++;//行数加加
        printf("%s",buf);
        if(len == num)
            break;
    }
/*******************************/
    //关闭文件
    fclose(fp);
    return 0;
}
