#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("hello\n");
    
    FILE *fp = freopen("a.txt","w+",stdout);//将stout流定位到"a.txt"中
    printf("world3\n");
    
    freopen("/dev/tty","r+",stdout);//将stout流定位到终端
    printf("I love china\n");
    fclose(fp);
    return 0;
}
