#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //1.创建数据报套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    //2.填充通信结构体 ipv4 广播地址  port(接收方)
    struct sockaddr_in saddr, addr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    socklen_t len = sizeof(addr);
    //3.绑定
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    char buf[128];
    while (1) //发送接收消息
    {
        recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &len);
        printf("%s %d:%s\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), buf);
    }
    close(sockfd);
    return 0;
}
