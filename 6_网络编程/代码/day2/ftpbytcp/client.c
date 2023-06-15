#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void show(void);
void client_list(int sockfd, char *buf, int size);
//get: 下载服务器对应普通文件到本地
void client_get(int sockfd, char *buf, int size);
//put: 上传客户端路径对应普通文件到服务器路径下
void client_put(int sockfd, char *buf, int size);

// void putFileToServer(int sockfd, char *buf);

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
    char buf[128];
    int recvbyte; //接收服务器数据recv返回值
    while (1)
    {
        show();
        //3.发送数据
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        send(sockfd, buf, sizeof(buf), 0);

        if (strncmp(buf, "list", 4) == 0)
        { //获取到服务器端的文件名字
            client_list(sockfd, buf, sizeof(buf));
        }
        else if (strncmp(buf, "put ", 4) == 0) //上传文件
        {
            client_put(sockfd, buf, sizeof(buf));
            // putFileToServer(sockfd, buf);
        }
        else if (strncmp(buf, "get ", 4) == 0)
        {
            client_get(sockfd, buf, sizeof(buf));
        }
        else if(strncmp(buf,"quit",4) == 0)
        {
            break;
        }
    }
    //5.关闭套接字
    close(sockfd);

    return 0;
}
//函数：接收打印文件名
void client_list(int sockfd, char *buf, int size)
{
    while (1)
    {
        if (recv(sockfd, buf, size, 0) < 0)
        {
            perror("list recv err.");
            return;
        }
        if (strncmp(buf, "server_send_end", 15) == 0)
        {
            break;
        }
        printf("%s\n", buf);
    }
}
//put: 上传客户端路径对应普通文件到服务器路径下
void client_put(int sockfd, char *buf, int size)
{
    //1.打开文件，只读方式
    int fd = open(buf + 4, O_RDONLY);
    if (fd < 0)
    {
        perror("client_put open file err.");
        return;
    }
    //2.读取文件内容，发送内容到客户端
    int ret;
    if ((ret = read(fd, buf, size - 1)) != 0)
    {
        buf[ret] = '\0';
        send(sockfd, buf, size, 0);
    }
    //发送结束标志
    strcpy(buf, "send end");
    send(sockfd, buf, size, 0);
}
//get: 下载服务器对应普通文件到本地
void client_get(int sockfd, char *buf, int size)
{
    //1.打开并新建文件
    int fd = open(buf + 4, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("client_get file open err.");
        return;
    }
    //2.接受服务端传过来的文件内容
    int recvbyte;
    while (1)
    {
        if ((recvbyte = recv(sockfd, buf, size, 0)) < 0)
        {
            perror("recv err.");
            return;
        }
        if (strncmp(buf, "send end", 8) == 0)
            break;
        //3.写到文件中
        write(fd, buf, strlen(buf));
    }
}
#if 0
void putFileToServer(int sockfd, char *buf)
{
    char buf2[128];
    char *filename = buf + 4;
    int src = open(filename, O_RDONLY);
    if (src < 0)
    {
        perror("open src error");
        return;
    }
    printf("open success...\n");
    ssize_t s;
    while ((s = read(src, buf2, 128)) != 0)
    {
        send(sockfd, buf2, s, 0);
    }
    //发送client文件内容发送结束标志
    strcpy(buf2, "client send file end");
    send(sockfd, buf2, sizeof(buf), 0);
}
#endif
void show(void)
{
    printf("-----------------------------------\n");
    printf("-------------list------------------\n");
    printf("-------------put filename----------\n");
    printf("-------------get filename----------\n");
    printf("-------------quit------------------\n");
    printf("-----------------------------------\n");
}