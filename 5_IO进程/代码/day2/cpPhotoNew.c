#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BYTE unsigned char
int main(){
    BYTE *buffer;

    FILE *pixmap = fopen("./ptoto.png","r");

    fseek(pixmap,0, SEEK_END);
    int length = ftell(pixmap);//读取图片的大小长度

    FILE *fp = fopen("./newphoto2.png","w+");

    buffer = (BYTE *)malloc(length*sizeof(BYTE));

    fseek(pixmap, 0, SEEK_SET);//把光标设置到文件的开头

    while(0 !=fread(buffer,sizeof(BYTE),length,pixmap))
    {
            printf("%s\n----%ld",buffer,strlen(buffer));
            fwrite(buffer,sizeof(BYTE),length,fp);
    }

    fclose(pixmap);
    fclose(fp);
}