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

//消息对应的结构体(保证客户端服务端同一个协议)
typedef struct msg_t
{
    int type;       //L C  Q
    char name[32];  //用户名
    char text[128]; //消息正文
} MSG_t;

//枚举，表示“登录、聊天、退出”
enum un
{
    login,
    chat,
    quit,
};

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Please input:%s <ip> <port>\n", argv[0]);
        return 0;
    }
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("sockfd err.");
        return -1;
    }

    //填充服务端的通信结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));      //port
    saddr.sin_addr.s_addr = inet_addr(argv[1]); //ip

    socklen_t len = sizeof(saddr);
    MSG_t msg; //创建消息结构体变量

    //客户端上来先登录。给服务端发送登录消息，以便服务端获取到当前客户端的连接信息
    printf("---请用户登录---\n");
    printf("请输入用户名：");
    fgets(msg.name, 32, stdin);
    if (msg.name[strlen(msg.name) - 1] == '\n') //剔除换行符，改为'\0'
        msg.name[strlen(msg.name) - 1] = '\0';
    msg.type = login; //将消息类型设置为login
    if (sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, len) < 0)
    {
        perror("sendto login err.");
        return -1;
    }

    pid_t pid = fork(); //创建子进程
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
            fgets(msg.text, sizeof(msg.text), stdin);
            if (msg.text[strlen(msg.text) - 1] == '\n') //剔除消息正文的换行符
                msg.text[strlen(msg.text) - 1] = '\0';
            if (strcmp(msg.text, "quit") == 0) //客户端消息为"quit"退出命令
            {
                msg.type = quit; //消息类型设置为“quit”
                sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, len);
                kill(pid, SIGKILL); //杀死子进程
                wait(NULL);         //等待子进程结束
                exit(-1);           //父进程退出
            }
            else //执行到这，消息肯定为聊天类型的
            {
                msg.type = chat; //消息类型设置为“chat”
                sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, len);
            }
        }
    }
    close(sockfd);
    return 0;
}
