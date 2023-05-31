#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H
#include <stdio.h>
#include <stdlib.h>
typedef int datatype;
typedef struct node
{
	datatype data;
	struct node *next;
}linkqueue_node_t,*linkqueue_list_t;
//定义头尾指针的结构体
typedef struct
{
	linkqueue_list_t front;//队列头指针
	linkqueue_list_t rear; //队尾指针
}linkqueue_t;//后面要申请空间来使用

//1.创建一个空的队列
linkqueue_t *CreateEmptyLinkQueue();
//2.入队data
int InlinkQueue(linkqueue_t *p,datatype data);
//3.出队(方法一)
datatype OutLinkQueue1(linkqueue_t *p);
//3.出队(方法二)
datatype OutLinkQueue2(linkqueue_t *p);
//4.队列判空
int IsEpLinkQueue(linkqueue_t *p);
//5.求队列长度
int LengthLinkQueue(linkqueue_t *p);
//6.清空队列
void ClearLinkQueue(linkqueue_t *p);

#endif
