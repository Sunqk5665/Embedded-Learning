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
#include <poll.h>

//IO多路复用-poll

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
    /*****IO多路复用*********************/
    //
    struct pollfd fds[100] = {};
    int last = -1;
    //将关心的文件描述符添加到pollfd结构体中
    fds[++last].fd = 0;
    fds[last].events = POLLIN;

    fds[++last].fd = sockfd;
    fds[last].events = POLLIN;

    char buf[128];
    /*************************************/

    socklen_t len = sizeof(caddr);
    while (1)
    {
        /***轮循监听IO及处理IO**********************/
        //c.监听
        // int ret = poll(fds, last + 1, -1);
        int ret = poll(fds, last + 1, 2000);
        if (ret < 0)
        {
            perror("poll err.");
            return -1;
        }
        else if (ret == 0)
        {
            printf("timed out---------------------\n");
            continue;
            // return -1;
        }
        else
        {
            printf("poll ok...\n");
        }

        //d.有一个或多个IO准备好就返回
        //e.判断哪个文件描述符产生事件
        for (int i = 0; i <= last; i++)
        {
            if (fds[i].revents == POLLIN)//判断当前结构体数组成员的revents是否是读事件(POLLIN)
            {
                if (fds[i].fd == 0)//是读事件且为键盘输入描述符
                {
                    fgets(buf, sizeof(buf), stdin);
                    printf("key:%s\n", buf);
                    //服务端向已链接的客户端发送通知
                    for (int j = 2; j <= last; j++)
                    {
                        send(fds[j].fd, buf, sizeof(buf), 0);
                    }
                }
                else if (fds[i].fd == sockfd)//是读事件且为sockfd描述符
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

                    fds[++last].fd = acceptfd; //将通信描述符添加到结构体数组中去
                    fds[last].events = POLLIN; //修改其事件为读事件(POLLIN)
                }
                else //是读事件且为acceptfd通信描述符，则进行数据的接收
                {
                    int recvbyte = recv(fds[i].fd, buf, sizeof(buf), 0);
                    if (recvbyte < 0)
                    {
                        perror("recv err.");
                        return -1;
                    }
                    else if (recvbyte == 0)
                    {
                        printf("%d client exit.\n", fds[i].fd);
                        close(fds[i].fd); //关闭该acceptfd
                        //从表中删除该acceptfd
                        fds[i--] = fds[last--];
                        // fds[i] = fds[last];
                        // last--;
                        // i--;
                    }
                    else
                    {
                        printf("%d client:%s\n", fds[i].fd, buf);
                    }
                }
            }
        }
    }
    close(sockfd);
    return 0;
}