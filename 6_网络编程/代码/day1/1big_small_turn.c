#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    int a = 0x12345678;
    //将主机的unsigned long值转换成网络字节顺序（32位）
    int da = htonl(a);
    printf("da=%#x\n",da);
    //网络字节顺序（32位）转为主机字节
    int xiao = ntohl(da);
    printf("xiao=%#x\n",xiao);
    return 0;
}
