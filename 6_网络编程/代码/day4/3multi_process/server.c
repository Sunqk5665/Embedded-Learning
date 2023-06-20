/*
-----多进程实现并发服务器-----
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#if 1
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
    saddr.sin_family = AF_INET;            //ipv4
    saddr.sin_port = htons(atoi(argv[1])); //端口
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    //2.绑定套接字
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    printf("bind ok...\n");
    //3.监听，将主动套接字转为被动套接字
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok...\n");

    socklen_t len = sizeof(caddr);
    while (1)
    {
        //4.accept，阻塞等待客户端链接，成功返回一个新的通信描述符
        acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
        if (acceptfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        else
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork err.");
                return -1;
            }
            else if (pid == 0) //子进程
            {
                int recvbyte;
                char buf[128];
                //获取到请求链接服务器的客户端的ip和端口
                printf("acceptfd=%d\n", acceptfd);
                printf("client ip=%s port=%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
                while (1)
                {
                    //5.循环接收消息 recv
                    recvbyte = recv(acceptfd, buf, sizeof(buf), 0);
                    if (recvbyte < 0)
                    {
                        perror("recv err.");
                        return -1;
                    }
                    else if (recvbyte == 0)
                    {
                        printf("client%d exit...\n",acceptfd);
                        close(acceptfd);
                        exit(0);
                        break;
                    }
                    else
                    {
                        printf("client%d->buf:%s\n", acceptfd, buf);
                    }
                }
            }
            else //父进程
            {
            }
        }
    }
    close(sockfd);
    return 0;
}
#endif
