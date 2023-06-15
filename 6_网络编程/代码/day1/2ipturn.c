#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

int main(int argc, char const *argv[])
{
    int *sp = "192.168.1.55";
    //inet_addr：将一个点分十进制的IPv4转换成一个32位无符号整数
    unsigned int ch = inet_addr(sp);
    printf("%#x\n",ch);
    //inet_ntoa：将网络传输的二进制数值转化为成点分十进制的ip地址
    struct in_addr addr;
    addr.s_addr = ch;
    char *p = inet_ntoa(addr);
    printf("p=%s\n",p);

    return 0;
}
