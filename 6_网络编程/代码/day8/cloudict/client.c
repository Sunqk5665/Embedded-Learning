#include "head.h"

void do_register(int sockfd, MSG_t msg);
void do_login(int sockfd, MSG_t msg);
void do_quit(int sockfd, MSG_t msg);
void secondMenu(int sockfd, MSG_t msg);
void do_query(int sockfd, MSG_t msg);
void do_history(int sockfd, MSG_t msg);

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Please input:%s <ip> <port>\n", argv[0]);
        return 0;
    }
    //创建套接字
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    printf("sockfd=%d\n", sockfd);
    //填充服务端的通信结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));      //服务端端口
    saddr.sin_addr.s_addr = inet_addr(argv[1]); //服务端ip
    //请求连接
    int connectval;
    connectval = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (connectval < 0)
    {
        perror("connect err.");
        return -1;
    }
    printf("connect OK...\n");
    MSG_t msg;
    int opt;
    while (1)
    {
        printf("-------------------------------\n");
        printf("--1:register  2:login  3:quit--\n");
        printf("-------------------------------\n");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            do_register(sockfd, msg);
            break;
        case 2:
            do_login(sockfd, msg);
            break;
        case 3:
            do_quit(sockfd, msg);
            break;
        default:
            break;
        }
    }

    //5.关闭套接字
    close(sockfd);
    return 0;
}
void do_register(int sockfd, MSG_t msg)
{
    msg.type = regist;
    printf("please input your name: ");
    scanf("%s", msg.name);
    printf("please input your password: ");
    scanf("%s", msg.data);
    if (send(sockfd, &msg, sizeof(msg), 0) < 0)
    {
        perror("send err.");
        return;
    }
    if (recv(sockfd, &msg, sizeof(msg), 0) < 0)
    {
        perror("recv err.");
        return;
    }
    printf("%s\n", msg.data);
}
void do_login(int sockfd, MSG_t msg)
{
    msg.type = login;
    printf("please input your name:");
    scanf("%s", msg.name);
    printf("please input your password:");
    scanf("%s", msg.data);
    if (send(sockfd, &msg, sizeof(msg), 0) < 0)
    {
        perror("send err.");
        return;
    }
    if (recv(sockfd, &msg, sizeof(msg), 0) < 0)
    {
        perror("recv err.");
        return;
    }
    if (strcmp(msg.data, "login ok...") == 0) //登录成功
    {
        printf("%s\n", msg.data);
        //登录成功，则跳转到二级菜单
        secondMenu(sockfd, msg);
    }
    else //登录失败
    {
        printf("%s\n", msg.data);
        return;
    }
}
void do_quit(int sockfd, MSG_t msg)
{
    msg.type = quit;
    if (send(sockfd, &msg, sizeof(msg), 0) < 0)
    {
        perror("send err.");
        // return;
    }
    close(sockfd);
    exit(0); //推出进程
}

void secondMenu(int sockfd, MSG_t msg)
{
    while (1)
    {
        int opt;
        printf("*********************************************\n");
        printf("* 1: query_word  2: history_record  3: quit *\n");
        printf("*********************************************\n");
        printf("please choose : ");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            do_query(sockfd, msg);
            break;
        case 2:
            do_history(sockfd, msg);
            break;
        case 3:
            do_quit(sockfd, msg);
        }
    }
}
void do_query(int sockfd, MSG_t msg)
{
    msg.type = query;
    while (1)
    {
        printf("input word(# to quit):");
        scanf("%s", msg.data);
        if (strcmp(msg.data, "#") == 0)
        {
            break;
        }
        if (send(sockfd, &msg, sizeof(msg), 0) < 0)
        {
            perror("send err.");
            return;
        }
        if (recv(sockfd, &msg, sizeof(msg), 0) < 0)
        {
            perror("recv err.");
            return;
        }
        printf("%s\n", msg.data); //输出查询结果
    }
}
void do_history(int sockfd, MSG_t msg)
{
    msg.type = history;
    if (send(sockfd, &msg, sizeof(msg), 0) < 0)
    {
        perror("send err.");
        return;
    }
    //循环接收历史记录消息
    while (1)
    {
        if (recv(sockfd, &msg, sizeof(msg), 0) < 0)
        {
            perror("recv err.");
            return;
        }
        if (msg.data[0] == '#') //消息体第一个字符为'#'，则没有查询到历史记录
        {
            printf("History record not found!\n");
            break;
        }
        else if (msg.data[0] == '*') //消息体第一个字符为'*'，则发送历史记录结束
        {
            break;
        }
        else
        {
            printf("%s\n", msg.data);//输出历史记录
        }
    }
    return;
}