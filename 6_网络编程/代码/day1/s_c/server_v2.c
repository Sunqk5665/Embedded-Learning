#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#if 1
int main(int argc, char const *argv[])
{
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
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6666);
    saddr.sin_addr.s_addr = inet_addr("192.168.1.118");
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
    while (1)
    {
        //4.accept
        acceptfd = accept(sockfd, NULL, NULL);
        if (acceptfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        printf("acceptfd=%d\n", acceptfd);
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
#endif
#if 0
int main(int argc, char const *argv[])
{
    int sockfd, acceptfd;
    //1.创建socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    printf("sockfd=%d\n", sockfd);
    //填充IPV4通信结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6666);
    saddr.sin_addr.s_addr = inet_addr("192.168.1.118");
    //2.绑定bind
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    //3.listen
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok...\n");
    while (1)
    {
        //4.accept
        acceptfd = accept(sockfd, NULL, NULL);
        if (acceptfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        printf("acceptfd=%d\n",acceptfd);

        int recvbyte;
        char buf[128];
        while (1)
        {
            //5.recv
            recvbyte = recv(acceptfd, buf, sizeof(buf), 0);
            if (recvbyte < 0)
            {
                perror("recv err.");
                return -1;
            }
            else if (recvbyte == 0)
            {
                printf("client exit\n");
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
#endif