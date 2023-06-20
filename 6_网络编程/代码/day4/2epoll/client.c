#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Please input:%s <port>\n", argv[0]);
        return 0;
    }
    //1.创建套接字
    int sockfd;
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
    saddr.sin_port = htons(atoi(argv[2]));      //服务端端口
    saddr.sin_addr.s_addr = inet_addr(argv[1]); //ip
    //2.请求连接
    int connectval;
    connectval = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (connectval < 0)
    {
        perror("connect err.");
        return -1;
    }
    printf("connect OK...\n");

    //创建子进程
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork err.");
        return -1;
    }
    else if (pid == 0)
    {
        //读取服务端发来的数据
        int ret;
        char buf[128];
        while (1)
        {
            ret = recv(sockfd, buf, sizeof(buf), 0);
            if (ret < 0)
            {
                perror("recv err.");
                return -1;
            }
            else if(ret == 0)
            {
                perror("conection closed by server.");
                return -1;
            }
            else
            {
                printf("server:%s\n", buf);
            }
        }
    }
    else
    {
        while (1)
        {
            //3.发送数据
            char buf[128];
            //scanf("%s", buf);
            fgets(buf, 128, stdin);
            if (buf[strlen(buf) - 1] == '\n')
                buf[strlen(buf) - 1] = '\0';
            send(sockfd, buf, sizeof(buf), 0);
        }
    }

    //5.关闭套接字
    close(sockfd);

    return 0;
}
