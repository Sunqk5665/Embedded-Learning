#include "server.h"
//创建空的有头单向链表
link_node *CreatEpLinkList();
//登录
void login_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p);
//聊天
void chat_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p);
//退出
void quit_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Please input:%s <port>\n", argv[0]);
        return 0;
    }
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("sockfd err.");
        return -1;
    }
    //填充通信结构体(IPV4)
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
        if (msg.type == login) //接收到的客户端消息为“登录”类型
        {
            //调用登录函数
            login_fun(sockfd, msg, caddr, p);
        }
        else if (msg.type == chat) //接收到的客户端消息为“聊天”类型
        {
            //调用聊天函数
            chat_fun(sockfd, msg, caddr, p);
        }
        else if (msg.type == quit) //接收到的客户端消息为“退出”类型
        {
            //调用退出函数
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
    sprintf(msg.text, "[%s]上线了...\n", msg.name); //将客户端上线信息放入消息正文中
    printf("IP=%s,port=%d,[%s]上线了...\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port), msg.name);
    while (p->next != NULL) //将登录信息发送给其他客户端（不包括现在登录的客户端）
    {
        p = p->next;
        sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
    }
    //更新已建立连接的客户端：将当前登录的客户端所建立的通信描述符插入单链表尾部
    link_node *pnew = (link_node *)malloc(sizeof(link_node));
    pnew->addr = caddr;
    pnew->next = NULL;
    p->next = pnew;
}
//聊天函数
void chat_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p)
{
    printf("[%s]>>%s\n", msg.name, msg.text); //服务端打印一下当前聊天信息
    //将当前发消息的客户端的消息发送给其他客户端
    while (p->next != NULL)
    {
        p = p->next;
        if (memcmp(&caddr, &(p->addr), sizeof(caddr))) //相等返回0，这样保证消息不发给发送消息的客户端
        {
            sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
        }
    }
}
//退出函数
void quit_fun(int sockfd, MSG_t msg, struct sockaddr_in caddr, link_node *p)
{
    printf("[%s]退出了聊天室...\n", msg.name); //服务端打印一下当前推出聊天室的客户端信息
    link_node *pre, *pdel;                     //pre：指向p的前一个结点，pdel：指向要删除结点
    sprintf(msg.text, "退出了聊天室...\n");    //将客户端上线信息放入消息正文中，以便下面的消息推送
    while (p->next != NULL)
    {
        //在链表中找到当前退出客户端的caddr进行删除，以及其他已链接客户端的消息推送
        pre = p;
        p = p->next;
        if (!memcmp(&caddr, &(p->addr), sizeof(caddr))) //是要退出的客户端，删除
        {
            pdel = p;
            pre->next = p->next;
            free(pdel);
        }
        else //不是要退出的客户端，将退出的客户端的消息发送给其他客户端
        {
            //将退出的客户端信息发送给其他客户端（不包括自己）
            sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
        }
    }
}