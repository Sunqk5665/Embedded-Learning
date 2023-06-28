#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
 
int main(int argc, char const *argv[])
{
    char buf[512] = {};
    int asc;
    FILE *fp1 = fopen("dict.txt", "r+");
    FILE *fp2 = fopen("newdict.txt", "w");
 
    while (1)
    {
        while (1)
        {
            asc = fgetc(fp1);
            if (asc == ' ')
            {
                fseek(fp1, -1, SEEK_CUR);
                fputc('|', fp2);    //写入分隔符
                while (1)
                {
                    asc = fgetc(fp1);
                    if (asc != ' ')
                        break;    //删去多余空格
                }
                break;
            }
            else if (asc == EOF)
                break;
            fputc(asc, fp2);
        }
 
        fseek(fp1, -1, SEEK_CUR);    //此处需要向前移动一个位置，否则会吞掉一个字符
 
        while (1)
        {
            fgets(buf, sizeof(buf), fp1);
            fputs(buf, fp2);
            if (buf[strlen(buf) - 1] == '\n')
                break;
        }
        if (asc == EOF)
            break;
    }
    fclose(fp1);
    fclose(fp2);
 
    // remove("dict.txt");            //删除原文件
    // rename("123.txt", "dict.txt"); //将临时文件名改为原文件名
 
    return 0;
}