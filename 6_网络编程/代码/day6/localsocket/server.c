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
    //删除一下套接字文件，防止报错：Address already in use
    system("rm ./mysocket");
    // unlink("./mysocket");

    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    printf("bind ok...\n");

    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok...\n");
    // socklen_t len = sizeof(caddr);
    while (1)
    {
        // acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
        acceptfd = accept(sockfd, NULL,NULL);
        if (acceptfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        int recvbyte;
        char buf[128];
        //循环接收消息 recv
        while (1)
        {
            recvbyte = recv(acceptfd, buf, sizeof(buf), 0);
            if (recvbyte < 0)
            {
                perror("recv err.");
                return -1;
            }
            else if (recvbyte == 0)
            {
                printf("client exit...\n");
                break;
            }
            else
            {
                printf("buf:%s\n", buf);
            }
        }
        close(acceptfd);
    }
    close(sockfd);
    return 0;
}
