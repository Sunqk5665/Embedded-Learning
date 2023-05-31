#include "sequeue.h"

//1.创建一个空队列
sequeue_t *CreateEpSequeue()
{
	sequeue_t *p = (sequeue_t *)malloc(sizeof(sequeue_t));
	if(NULL == p)
	{
		printf("CreateEpSequeue malloc error!\n");
		return NULL;
	}
	p->front = 0;
	p->rear = 0;
	return p;
}

//2.入队data
int InSequeue(sequeue_t *p,datatype data)
{
	if(IsFullSequeue(p))
	{
		printf("InSequeue error!\n");
		return -1;
	}
	p->data[p->rear] = data;
	p->rear = (p->rear+1)%N;
	return 0;
}
//3.判断队满
int IsFullSequeue(sequeue_t *p)
{
	return (p->rear+1)%N == p->front;
}
//4.判断队空
int IsEpSequeue(sequeue_t *p)
{
	return p->rear == p->front;
}
//5.出队
int OutSequeue(sequeue_t *p)
{
	if(IsEpSequeue(p))
	{
		printf("OutSequeue error!\n");
		return -1;
	}
	datatype temp = p->data[p->front];
	p->front = (p->front+1)%N;
	return temp;
}
//6.求队列长度
int LengthSequeue(sequeue_t *p)
{
	return (p->rear - p->front + N)%N;
}
//7.清空队列
void ClearSequeue(sequeue_t *p)
{
	while(!IsEpSequeue(p))
	{
		OutSequeue(p);
	}
	p->front = 0;
	p->rear = 0;
}



