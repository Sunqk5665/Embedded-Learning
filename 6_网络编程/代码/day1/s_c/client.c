#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char const *argv[])
{
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
    saddr.sin_port = htons(6666);
    saddr.sin_addr.s_addr = inet_addr("192.168.1.118");
    //2.请求连接
    int connectval;
    connectval = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (connectval < 0)
    {
        perror("connect err.");
        return -1;
    }
    printf("connect OK...\n");
    char buf[128];
    while (1)
    {
        //3.发送数据
        //scanf("%s", buf);
        fgets(buf,128,stdin);
        if(buf[strlen(buf)-1] == '\n')
            buf[strlen(buf)-1] = '\0';
        send(sockfd, buf, sizeof(buf), 0);
        //4.读取数据
    }
    //5.关闭套接字
    close(sockfd);

    return 0;
}
