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
#include <sys/epoll.h>

/*********epoll实现IO多路复用***********/
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

    socklen_t len = sizeof(caddr);
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
    /*****epoll*********************/
    //引入epoll   0 sockfd
    struct epoll_event event;      //暂时保存关心的文件描述符
    struct epoll_event revent[20]; //保存从链表中获取的事件
    //1、创建树
    int epfd = epoll_create(1);
    //2、将关心文件描述符添加到树上
    event.data.fd = 0;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);

    event.data.fd = sockfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);

    char buf[128];
    /*************************************/

    while (1)
    {
        //3.调用函数epoll_wait
        //阻塞等待链表中有通知的事件拿过来处理
        // int ret = epoll_wait(epfd, revent, 20, -1);
        int ret = epoll_wait(epfd, revent, 20, 2000);//超时设置2秒
        if (ret < 0)
        {
            perror("epoll err.");
            return -1;
        }
        else if(ret == 0)
        {
            printf("time out----------\n");
            continue;
        }
        //d.有一个或多个IO准备好就返回
        //e.判断哪个文件描述符产生事件
        for (int i = 0; i < ret; i++)
        {
            if (revent[i].data.fd == 0)
            {
                fgets(buf, sizeof(buf), stdin);
                printf("key:%s\n", buf);
                //服务端向已链接的客户端发送通知
            }
            else if (revent[i].data.fd == sockfd)
            {
                //4.阻塞等待客户端链接 accept  链接成功会得到一个和这个客户端通信的文件描述符
                acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
                if (acceptfd < 0)
                {
                    perror("accept err.");
                    return -1;
                }
                //获取到请求链接服务器的客户端的ip和端口
                printf("acceptfd=%d\n", acceptfd);
                printf("ip=%s port=%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
                //将通信描述符添加到表中去
                event.data.fd = acceptfd;
                event.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &event);
            }
            else
            {
                int recvbyte = recv(revent[i].data.fd, buf, sizeof(buf), 0);
                if (recvbyte < 0)
                {
                    perror("recv err.");
                    return -1;
                }
                else if (recvbyte == 0)
                {
                    printf("%d client exit.\n", revent[i].data.fd);
                    close(revent[i].data.fd); //关闭该acceptfd
                    //从表中删除该acceptfd
                    epoll_ctl(epfd, EPOLL_CTL_DEL, revent[i].data.fd, NULL);
                }
                else
                {
                    printf("%d client:%s\n", revent[i].data.fd, buf);
                }
            }
        }
    }
    close(sockfd);
    return 0;
}