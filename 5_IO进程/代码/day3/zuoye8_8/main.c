/*
    编程读写一个文件test.txt，每隔1秒向文件中写入一行数据，类似这样： 
    1,2007-7-30 15:16:42  
    2,2007-7-30 15:16:43
     ......
    该程序应该无限循环，直到按Ctrl+C中断程序。
    再次启动程序写文件时可以追加到原文件之后，并且序号能够接续上次的序号
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *fp = fopen("test.txt", "a+");
    if (fp == NULL)
    {
        perror("fopen err!\n");
        return -1;
    }
    /*******取行号（行号作为追加数据的序号）********/
    fseek(fp, 0, SEEK_SET); // 将文件流指针定位到文件其实位置，保证每次运行本程序都算一遍当前行数
    //下面算文件行数
    char buf2[32] = {0};
    int len = 0;
    while (fgets(buf2, 32, fp) != NULL)
    {
        if (buf2[strlen(buf2) - 1] == '\n') //'\n'作为行结束标志
            len++;
    }
    /********取行号结束***********************/

    /********往指定文件循环输入当前时间数据********/
    time_t t;
    struct tm *lt = NULL;
    while (1)
    {
        //获取当前时间
        t = time(NULL);
        lt = localtime(&t);

        char buf[32] = {0};

        sprintf(buf, "%d-%d-%d %d:%d:%d",
                lt->tm_year + 1900,
                lt->tm_mon + 1,
                lt->tm_mday,
                lt->tm_hour,
                lt->tm_min,
                lt->tm_sec); //将当前时间输入到buf中
        //printf("%s",buf);
        fprintf(fp, "%d, %s\n", ++len, buf); //将时间格式化输出到流文件中
                                      // 先将数据输出到缓冲区中（全缓冲），直到缓冲区满才将数据写入到文件中
                                      // 因此需要强制刷新缓冲区
        fflush(NULL); // 强制刷新，即刷新全缓冲
        sleep(1);     // 睡眠间隔时间为1 seconds
    }
    /***********************************/
    fclose(fp); //关闭文件
    return 0;
}
