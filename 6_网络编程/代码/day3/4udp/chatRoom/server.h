#ifndef _SERVER_H_
#define _SERVER_H_
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

//定义链表节点结构体,用来存放客户端的通信结构体
typedef struct node
{
    struct sockaddr_in addr;
    struct node *next;
} link_node;

//消息对应的结构体(保证客户端服务端同一个协议)
typedef struct msg_t
{
    int type;       //L C  Q    enum un{login,chat,quit};
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

#endif