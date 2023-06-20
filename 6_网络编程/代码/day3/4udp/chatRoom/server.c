#include "server.h"

link_node *CreatEpLinkList(); //创建空的有头单向链表
//登录函数
void login_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p);
//聊天函数
void chat_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p);
//退出函数
void quit_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p);

int main(int argc, char const *argv[])
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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

    socklen_t len = sizeof(caddr);
    link_node *p = CreatEpLinkList(); //创建空的有头单向链表

    MSG_t msg; //创建消息结构体变量

    while (1)
    {
        if (recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&caddr, &len) < 0)
        {
            perror("recvfrom err.");
            return -1;
        }
        if (msg.type == login)
        {
            login_fun(sockfd, msg, caddr, p); //登录函数
        }
        else if (msg.type == chat)
        {
            chat_fun(sockfd, msg, caddr, p); //聊天函数
        }
        else if (msg.type == quit)
        {
            quit_fun(sockfd, msg, caddr, p);
        }
    }
    close(sockfd);
    free(p); //释放空间
    p = NULL;
    return 0;
}
//创建空的有头单向链表
link_node *CreatEpLinkList()
{
    link_node *h = (link_node *)malloc(sizeof(link_node));
    if (NULL == h)
    {
        printf("CreatEpLinkList error!\n");
        return NULL;
    }
    h->next == NULL;
    return h;
}
//登录函数
void login_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p)
{
    sprintf(msg.text, "[%s]上线了...\n", msg.name);
    printf("IP=%s,port=%d,%s上线了...\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port), msg.name);
    while (p->next != NULL) //将登录信息发送给其他客户端（不包括自己）
    {
        p = p->next;
        sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
    }
    //将建立的通信描述符插入单链表尾部
    link_node *pnew = (link_node *)malloc(sizeof(link_node));
    pnew->addr = caddr;
    pnew->next = NULL;
    p->next = pnew;
}
//聊天函数
void chat_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p)
{
    printf("[%s]>>%s\n", msg.name, msg.text);
    while (p->next != NULL)
    {
        p = p->next;
        if (memcmp(&caddr, &(p->addr), sizeof(caddr))) //相等返回0
        {
            sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
        }
    }
}
//退出函数
void quit_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p)
{
    printf("[%s]退出了聊天室...\n", msg.name);
    link_node *pre, *pdel; //存储p的前一个节点
    sprintf(msg.text, "退出了聊天室...\n");
    while (p->next != NULL)
    {
        pre = p;
        p = p->next;
        if (!memcmp(&caddr, &(p->addr), sizeof(caddr))) //找到要删除的caddr
        {
            pdel = p;
            pre->next = p->next;
            free(pdel);
        }
        else //不是要删除的节点
        {
            //将退出的客户端信息发送给其他客户端（不包括自己）
            sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
        }
        //sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
    }
}