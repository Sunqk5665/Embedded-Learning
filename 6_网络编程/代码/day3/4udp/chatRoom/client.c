#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

//消息对应的结构体(同一个协议)
typedef struct msg_t
{
    int type;       //L C  Q    enum un{login,chat,quit};
    char name[32];  //用户名
    char text[128]; //消息正文
} MSG_t;

enum un
{
    login,
    chat,
    quit,
};

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

    socklen_t len = sizeof(saddr);
    MSG_t msg; //创建消息结构体变量
    printf("---请用户登录---\n");
    msg.type = login;
    printf("请输入用户名：");
    fgets(msg.name, 32, stdin);
    if (msg.name[strlen(msg.name) - 1] == '\n') //剔除换行符
        msg.name[strlen(msg.name) - 1] = '\0';
    //给服务端发送登录消息
    if (sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, len) < 0)
    {
        perror("sendto login err.");
        return -1;
    }

    //循环收发消息 sendto
    char buf[128];

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork err.");
        return -1;
    }
    else if (pid == 0) //子进程接收server端消息
    {
        while (1)
        {
            recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, &len);
            if (msg.type)
                printf("[%s]:%s\n", msg.name, msg.text);
        }
    }
    else //父进程向server端发送消息
    {
        while (1)
        {
            fgets(msg.text, sizeof(buf), stdin);
            if (msg.text[strlen(msg.text) - 1] == '\n') //剔除换行符
                msg.text[strlen(msg.text) - 1] = '\0';
            if (strcmp(msg.text, "quit") == 0)
            {
                msg.type = quit;
                sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, len);
                kill(pid, SIGKILL); //杀死子进程
                wait(NULL);
                exit(-1);
            }
            else
            {
                msg.type = chat;
                sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, len);
            }
        }
    }
    close(sockfd);
    return 0;
}
