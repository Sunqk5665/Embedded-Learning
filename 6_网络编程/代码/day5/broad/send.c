#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("sockfd err.");
        return -1;
    }

    int on = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    // 填充IPV4通信结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));//端口
    saddr.sin_addr.s_addr = inet_addr("192.168.1.255");// 广播地址

    //recvfrom
    char buf[128];
    socklen_t len = sizeof(saddr);

    while (1)
    {
        strcpy(buf, "hello");
        // fgets(buf, sizeof(buf), stdin);
        sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&saddr, sizeof(saddr));
        sleep(1);
    }
    close(sockfd);
    return 0;
}
