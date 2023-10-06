/*实现wc -l的功能*/
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    if(NULL == fp)
    {
        perror("fopen err");
        return -1;
    } 
    int hang = 0;
    char buf[32];
#if 0
    while(1)
    {
        if(fgets(buf,32,fp)!=NULL)
        {
            if(buf[strlen(buf)-1]=='\n') //取完一行
                hang++;
        }
        else
            break;
    }
#endif
#if 1
    while(fgets(buf,32,fp)!=NULL)
    {
        if(buf[strlen(buf)-1]=='\n')
            hang++;
    }
#endif
    printf("%d %s\n",hang,argv[1]);
    fclose(fp);
    return 0;
}
