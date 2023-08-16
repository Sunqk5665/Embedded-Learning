//实现 head -n 文件名   ./a.out -3 filename
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    if (argc != 3) //判断输入格式是否正确
    {
        printf("Please input:%s -n <filename>", argv[0]);
    }
    FILE *fp = fopen(argv[2], "r");
    if (NULL == fp)
    {
        perror("fopen err");
        return -1;
    }
    //获取要输出几行
    int num = -atoi(argv[1]); // 行数转换
    // int num = atoi(argv[1]+1);  // 首地址移动
    char buf[32] = {0};

    int len = 0;
    //读取前n行
    while (fgets(buf, 32, fp) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            len++;
        }
        printf("%s", buf);
        if(len == num)
            break;
    }
    //关闭文件
    fclose(fp);
    return 0;
}
