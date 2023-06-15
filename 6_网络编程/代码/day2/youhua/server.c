/*
代码优化：
1.去掉fgets获取的多余的'\n'.
   if(buf[strlen(buf)-1] == '\n')//去掉fgets获取的'\n'
         buf[strlen(buf)-1] ='\0';
2.端口和ip地址通过命令行传参到代码中。
3.设置客户端退出，服务器结束循环接收。
    通过recv返回值为0判断客户端是否退出
4.设置来电显示功能，获取到请求链接服务器的客户端的ip和端口。
5.设置服务器端自动获取自己的ip地址。
   INADDR_ANY  "0.0.0.0"
6.实现循环服务器，服务器不退出，当链接服务器的客户端退出，服务器等到下一个客户端链接。
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Please input:%s <ip> <port>\n", argv[0]);
        return 0;
    }
    //1.创建套接字
    int sockfd, acceptfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    printf("sockfd=%d\n", sockfd);
    //填充IPV4通信结构体
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1])); //端口
    // saddr.sin_addr.s_addr = inet_addr(argv[1]);//ip
    // 设置自动获取本机ip
    // saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    //2.绑定套接字
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    printf("bind ok...\n");
    //3.监听
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok...\n");

    socklen_t len = sizeof(caddr);
    while (1)
    {
        //4.accept
        acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
        if (acceptfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        printf("acceptfd=%d\n", acceptfd);
        printf("client ip=%s port=%d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
        //5.循环接收消息 recv
        int recvbyte;
        char buf[128];
        while (1)
        {
            recvbyte = recv(acceptfd, buf, sizeof(buf), 0);
            if (recvbyte < 0)
            {
                perror("recv err.");
                return -1;
            }
            else if (recvbyte == 0)
            {
                printf("client exit...\n");
                break;
            }
            else
            {
                printf("buf:%s\n", buf);
            }
        }
        close(acceptfd);
    }
    close(sockfd);
    return 0;
}