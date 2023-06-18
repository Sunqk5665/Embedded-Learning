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
    if (sockfd < 0)
    {
        perror("sockfd err.");
        return -1;
    }
    //
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));      //port
    saddr.sin_addr.s_addr = inet_addr(argv[1]); //ip

    ////循环收发消息 sendto
    char buf[128];
    socklen_t len = sizeof(saddr);
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&saddr, len) < 0)
        {
            perror("sendto err.");
            return -1;
        }
        recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&saddr,&len);
        printf("server:%s\n",buf);
    }
    close(sockfd);
    return 0;
}
