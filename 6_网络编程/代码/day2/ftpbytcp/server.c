/*
项目功能介绍：
   均有服务器和客户端代码，基于TCP写的。
   在同一路径下，将客户端可执行代码复制到其他的路径下，接下来在不同的路径下运行服务器和客户端。
      相当于另外一台电脑在访问服务器。
客户端和服务器链接成功后出现以下提示：四个功能
***************list************** //列出服务器所在目录下的文件名(除目录不显示)
***********put filename********** //上传一个文件
***********get filename********** //从服务器所在路径下载文件
**************quit*************** //退出(可只退出客户端，服务器等待下一个客户端链接)
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

//函数声明
void server_list(int acceptfd, char *buf, int size); //列出制定目录下的文件
//get:打开已存在文件，读文件内容发送给客户端
void server_get(int acceptfd, char *buf, int size);
//put: 接受客户端文件到服务端当前目录
void server_pull(int acceptfd, char *buf, int size);

//void recvFile(int acceptfd, char *buf);              //server接收client文件

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
    // saddr.sin_addr.s_addr = inet_addr(argv[1]);//ip
    // 设置自动获取本机ip
    // saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // saddr.sin_addr.s_addr = INADDR_ANY;
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

    socklen_t len = sizeof(caddr);
    while (1)
    {
        //4.accept
        acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
        if (acceptfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        printf("acceptfd=%d\n", acceptfd);
        printf("client ip=%s port=%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

        int recvbyte;
        char buf[128];
        while (1)
        {
            //5.循环接收消息 recv
            recvbyte = recv(acceptfd, buf, sizeof(buf), 0);
            if (recvbyte < 0)
            {
                perror("recv err.");
                return -1;
            }
            else if (recvbyte == 0)
            {
                //printf("client exit...\n");
                break;
            }
            else
            {
                printf("buf:%s\n", buf);
                if (strcmp(buf, "list") == 0) //列出服务器所在目录下的文件名(除目录不显示)
                {
                    // printf("list\n");
                    server_list(acceptfd, buf, sizeof(buf));
                }
                else if (strncmp(buf, "put", 3) == 0) //server接收client文件， buf:"put filename"
                {
                    server_pull(acceptfd, buf, sizeof(buf));
                    // recvFile(acceptfd, buf);
                }
                else if (strncmp(buf, "get ", 4) == 0)
                {
                    server_get(acceptfd, buf, sizeof(buf));
                }
                else if (strncmp(buf, "quit", 4) == 0)
                {
                    printf("client exit...\n");
                    continue;
                }
            }
        }
        close(acceptfd);
    }
    close(sockfd);
    return 0;
}
//列出制定目录下的文件
void server_list(int acceptfd, char *buf, int size)
{
    printf("------------------\n");
    //1.打开当前目录
    DIR *dir = opendir("./");
    if (dir == NULL)
    {
        perror("opendir err");
        return;
    }
    printf("opendir ok...\n");
    //2.循环读目录
    struct dirent *d;
    struct stat st;
    while ((d = readdir(dir)) != NULL)
    {
        if (d->d_name[0] == '.') //剔除隐藏文件 . and ..
        {
            continue;
        }
        //3.判断是否为普通文件，是文件名发送给客户端
        //stat获取文件属性的函数
        stat(d->d_name, &st);
        if (S_ISREG(st.st_mode))
        {
            send(acceptfd, d->d_name, size, 0);
        }
    }
    //结束标志：server_send_end标志->client
    send(acceptfd, "server_send_end", sizeof("server_send_end"), 0);
    // //发送结束标志
    // strcpy(buf,"send end");
    // send(acceptfd,buf,size,0);

    closedir(dir);
}
//put: 接受客户端文件到服务端当前目录
void server_pull(int acceptfd, char *buf, int size)
{
    //1.打开文件,写、创建、清空
    int fd = open(buf + 4, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("server_pull open file err.");
        return;
    }
    //2.接收客户端文件内容并写到文件中
    int recvbyte;
    while (1)
    {
        if ((recvbyte = recv(acceptfd, buf, size, 0)) < 0)
        {
            perror("server_pull recv err");
            return;
        }
        if (strncmp(buf, "send end", 8) == 0)
            break;
        write(fd, buf, strlen(buf));
    }
}
//get: 打开已存在文件，读文件内容发送给客户端
void server_get(int acceptfd, char *buf, int size)
{
    //1.打开文件，只读方式
    int fd = open(buf + 4, O_RDONLY);
    if (fd < 0)
    {
        perror("server file open err.");
        return;
    }
    //2.读文件，发送读取内容
    int ret;

    while ((ret = read(fd, buf, size - 1)) != 0)
    {
        buf[ret] = '\0';
        send(acceptfd, buf, size, 0);
    }
    //发送结束标志
    strcpy(buf, "send end");
    send(acceptfd, buf, size, 0);
}

#if 0
void recvFile(int acceptfd, char *buf)
{
    int fd = open(buf+4, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("open err");
        return;
    }
    while (1)
    {
        recv(acceptfd, buf, sizeof(buf), 0);
        if (strncmp(buf, "client send file end", 20) == 0)
        {
            break;
        }
        write(fd, buf, sizeof(buf));
    }
}
#endif