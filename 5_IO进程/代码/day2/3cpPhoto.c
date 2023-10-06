/*练习：实现cp fread fwrite 复制一张图片
*/
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if(argc != 3)  // 命令行参数个数判断
    {
        printf("Please input:%s <srcfile> <destfile>",argv[0]);
        return -1;
    }
    FILE *src = fopen(argv[1],"r");
    if(NULL == src)
    {
        perror("fopen src err");
        return -1;
    }
    printf("fopen src success!\n");
    FILE *dest = fopen(argv[2],"w");
    if(NULL == dest)
    {
        perror("fopen dest err");
        return -1;
    }
    
    char buf[32] = {0};//用char比用int好
    size_t s; //为无符号整型
    //循环读写
    while ((s=fread(buf,sizeof(char),32,src)) != 0)
    {
        fwrite(buf,sizeof(char),s,dest);
    }
    //关闭文件流
    fclose(src);
    fclose(dest);
    return 0;
}
