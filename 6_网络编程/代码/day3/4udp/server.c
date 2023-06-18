#include <stdio.h>
#include <sys/types.h> /* See NOTES */
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
    // int clintfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("sockfd err.");
        return -1;
    }
    //填充IPV4通信结构体
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    //bind
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    //recvfrom
    char buf[128];
    socklen_t len = sizeof(caddr);
    while (1)
    {
        if (recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&caddr, &len) < 0)
        {
            perror("recvfrom err.");
            return -1;
        }
        printf("clientIP=%s,clientPport=%d\nmessgge:%s\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port), buf);
        strcpy(buf,"hello");
        sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&caddr,len);
    }
    close(sockfd);
    return 0;
}
