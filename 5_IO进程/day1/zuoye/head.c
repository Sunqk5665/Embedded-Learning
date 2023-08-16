//实现 head -n 文件名   ./a.out -3 filename
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    if(argc != 3)//判断输入格式是否正确
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
    int num = atoi(argv[1]+1);  // 首地址移动
    char buf[32] = {0};
    
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
    while (fgets(buf,32,fp) != NULL) //若是num>文件实际行数，则打印全部内容
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
