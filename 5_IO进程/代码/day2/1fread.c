#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1],"w+");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    }
    printf("fopen success\n");
    float arr[3] = {1.23,4.56,7.89};

    fwrite(arr,sizeof(float),3,fp);//将arr中的内容写到fp
    float arr2[3] = {0};
    rewind(fp);//将文件流定位到文件起始位置
    fread(arr2,sizeof(float),3,fp);//将fp中内容写入arr2
    for(int i=0; i<3; i++)
    {
        printf("%.2f ",arr2[i]);
    }
    putchar(10);
    fclose(fp);
    return 0;
}
