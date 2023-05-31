#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_
#include <stdio.h>
#include <stdlib.h>
typedef int datatype;
typedef struct linkqueuenode
{
	datatype data;
	struct linkqueuenode *next;
}linkqueue_node_t,*linkqueue_list_t;
typedef struct
{
	linkqueue_list_t front;
	linkqueue_list_t rear;
}linkqueue_t;
//1.创建空队列
linkqueue_t *CreateLinkQueue();
//2.入队
int InLinkQueue(linkqueue_t *p,datatype data);
//3.出队
datatype OutLinkQueue(linkqueue_t *p);
//4.判断队空
int IsEpLinkQueue(linkqueue_t *p);
//5.求队列长度
int LengthLinkQueue(linkqueue_t *p);
//6.清空队列
void ClearLinkQueue(linkqueue_t *p);

#endif
