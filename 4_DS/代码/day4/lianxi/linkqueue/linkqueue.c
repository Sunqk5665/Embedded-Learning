#include "linkqueue.h"
//1.
linkqueue_t *CreateLinkQueue()
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
		printf("CreateLinkQueue malloc node failed!\n");
		return NULL;
	}
	p->front->next = NULL;
	p->rear = p->front;
	return p;
}
//2.入队
int InLinkQueue(linkqueue_t *p,datatype data)
{
	linkqueue_node_t *pnew = (linkqueue_node_t *)malloc(sizeof(linkqueue_node_t));
	if(NULL == pnew)
	{
		printf("InLinkQueue malloc pnew error!\n");
		return -1;
	}
	pnew->data = data;
	pnew->next = NULL;
	p->rear->next = pnew;
	p->rear = pnew;
	return 0;
}
//3.出队
datatype OutLinkQueue(linkqueue_t *p)
{
	if(IsEpLinkQueue(p))
	{
		printf("OutLinkQueue error,LinkQueue is Empty!\n");
		return -1;
	}
	linkqueue_node_t *pdel = p->front->next;
	datatype temp = pdel->data;
	p->front->next = pdel->next;
	free(pdel);
	pdel = NULL;
	return temp;
}
//4.判断队空
int IsEpLinkQueue(linkqueue_t *p)
{
	return p->front->next == NULL;
}
//5.求队列长度
int LengthLinkQueue(linkqueue_t *p)
{
	int len = 0;
	linkqueue_node_t *t = p->front;
	while(t->next != NULL)
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
		OutLinkQueue(p);
	}
}

