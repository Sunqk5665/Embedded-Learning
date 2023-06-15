#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //1.创建套接字
    int sockfd;
    int acceptfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err");
        return -1;
    }
    printf("sockfd=%d\n", sockfd);
    //填充IPV4 通信结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8888); //将一个无符号短整型(short)数值转换为网络字节序(即大端模式)
    saddr.sin_addr.s_addr = inet_addr("192.168.1.118");
    //2.绑定套接字 bind ->ip port
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err");
        return -1;
    }
    printf("bind ok...\n");
    //3.监听，将主动套接字变为被动套接字
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok.\n");
    //4.阻塞等待客户端连接。accept，链接成功会得到一个和这个客户端通信的文件描述符
    acceptfd = accept(sockfd, NULL, NULL);
    if (acceptfd < 0)
    {
        perror("accept err.");
        return -1;
    }
    printf("acceptfd=%d\n", acceptfd);
    //5.接收数据
    char buf[128] = {0};
    int recvbyte;
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
            printf("client exit\n");
            return 0;
        }
        else
        {
            printf("buf:%s\n", buf);
        }
    }
    close(acceptfd);
    close(sockfd);

    return 0;
}
