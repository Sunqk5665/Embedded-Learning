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
/*
监测键盘输入事件及客户端连接(sockfd)事件。实现TCP一个服务器多个客户端连接。同时实现响应多个客户但通信（所有acceptfd）。
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>

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
    /**引入->IO多路复用*********************/
    //a.创建一个表
    fd_set readfds, tempfds;
    FD_ZERO(&readfds); //清空表
    //b.将关心的文件描述符添加到表中
    FD_SET(0, &readfds);
    FD_SET(sockfd, &readfds);
    int maxfd = sockfd;
    char buf[128];
    /*************************************/

    socklen_t len = sizeof(caddr);
    while (1)
    {
        /***监听IO及处理IO**********************/
        //c.调用select函数监听
        tempfds = readfds;
        int ret = select(maxfd + 1, &tempfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select err.");
            return -1;
        }
        //d.有一个或多个IO准备好就返回
        //e.判断哪个文件描述符产生事件
        if (FD_ISSET(0, &tempfds))
        {
            fgets(buf, sizeof(buf), stdin);
            printf("key:%s\n", buf);
            //服务端向已链接的客户端发送通知
            for (int i = 4; i <= maxfd; i++)
            {
                if(FD_ISSET(i,&readfds))
                {
                    send(i,buf,sizeof(buf),0);
                }
            }
        }
        if (FD_ISSET(sockfd, &tempfds))
        {
            //4.accept
            acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
            if (acceptfd < 0)
            {
                perror("accept err.");
                return -1;
            }
            //获取到请求链接服务器的客户端的ip和端口
            printf("acceptfd=%d\n", acceptfd);
            printf("ip=%s port=%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

            FD_SET(acceptfd, &readfds); //将通信描述符添加到原表中去
            if (acceptfd > maxfd)
                maxfd = acceptfd;
        }
        for (int i = 4; i <= maxfd; i++)
        {
            if (FD_ISSET(i, &tempfds))
            {
                int recvbyte = recv(i, buf, sizeof(buf), 0);
                if (recvbyte < 0)
                {
                    perror("recv err.");
                    return -1;
                }
                else if (recvbyte == 0)
                {
                    printf("%d client exit.\n", i);
                    close(i);            //关闭该acceptfd
                    FD_CLR(i, &readfds); //清空原表中的acceptfd
                }
                else
                {
                    printf("%d client:%s\n", i, buf);
                }
            }
        }
        /************************************/
    }
    close(sockfd);
    return 0;
}