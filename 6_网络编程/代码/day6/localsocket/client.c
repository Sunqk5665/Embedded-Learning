#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>

int main(int argc, char const *argv[])
{
    int sockfd, acceptfd;
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }

    struct sockaddr_un myaddr;
    myaddr.sun_family = AF_UNIX;
    strcpy(myaddr.sun_path, "./mysocket"); //可以指定路径

    //2.请求连接
    int connectval;
    connectval = connect(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
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
        fgets(buf, 128, stdin);
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        send(sockfd, buf, sizeof(buf), 0);
    }
    close(sockfd);
    return 0;
}
