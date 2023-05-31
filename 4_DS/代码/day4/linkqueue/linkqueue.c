#include "linkqueue.h"

//1.创建一个空的队列
linkqueue_t *CreateEmptyLinkQueue()
{
	linkqueue_t *p = (linkqueue_t *)malloc(sizeof(linkqueue_t));
	if(NULL == p)
	{
		printf("linkqueue_t malloc failed!\n");
		return NULL;
	}
	p->front = (linkqueue_node_t *)malloc(sizeof(linkqueue_node_t));
	if(NULL == p->front)
	{
		printf("CreateEmptyLinkQueue malloc node failed!\n");
		return NULL;
	}
	p->front->next = NULL;
	p->rear = p->front;

	return p;
}
//2.入队data
int InlinkQueue(linkqueue_t *p,datatype data)
{
	linkqueue_node_t *pnew = (linkqueue_list_t)malloc(sizeof(linkqueue_node_t));
	if(NULL == pnew)
	{
		printf("pnew malloc failed!\n");
		return -1;
	}
	//初始化节点
	pnew->data = data;
	pnew->next = NULL;
	//队尾入队
	p->rear->next = pnew;
	p->rear = pnew;
	return 0;
}
//3.出队(方法一)
datatype OutLinkQueue1(linkqueue_t *p)
{
	if(IsEpLinkQueue(p))
	{
		printf("OutLinkQueue failed!\n");
		return -1;
	}
	linkqueue_node_t *pdel = p->front->next;
	datatype temp = pdel->data;

	p->front->next = pdel->next;

	free(pdel);
	pdel = NULL;
	return temp;	
}
//3.出队(方法二)
datatype OutLinkQueue2(linkqueue_t *p)
{
	if(IsEpLinkQueue(p))
	{
		printf("OutLinkQueue failed!\n");
		return -1;
	}
	linkqueue_node_t *pdel = p->front;
	p->front = pdel->next;
	free(pdel);
	pdel = NULL;
	
	return p->front->data;
}

//4.队列判空
int IsEpLinkQueue(linkqueue_t *p)
{
	return p->front->next == NULL;
}
//5.求队列长度
int LengthLinkQueue(linkqueue_t *p)
{
	int len = 0;
	if(IsEpLinkQueue(p))
	{
		printf("LengthLinkQueue error!\n");
		return -1;
	}
	linkqueue_node_t *t = p->front;

	while(t->next != NULL) //有头节点的判断
	{
		t = t->next;
		len++;
	}
	return len;
}
//6.清空队列
void ClearLinkQueue(linkqueue_t *p)
{
	while(!IsEpLinkQueue(p))
	{
		OutLinkQueue1(p);
	}
}
