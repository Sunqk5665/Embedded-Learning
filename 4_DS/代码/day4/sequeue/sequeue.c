#include "sequeue.h"

//1.创建一个空的队列
sequeue_t *CreateEmptySequeue()
{
    sequeue_t *p = (sequeue_t *)malloc(sizeof(sequeue_t));
    if(NULL == p)
    {
        printf("CreateEmptySequeue malloc error!\n");
        return NULL;
    }
    p->front = 0;
    p->rear = 0;
    return p;
}
//2.入队 data代表入队的数据
int InSequeue(sequeue_t *p,datatype data)
{
    if(IsFullSequeue(p))
    {
        printf("InSequeue failed!\n");
        return -1;
    }
    p->data[p->rear] = data;
    p->rear = (p->rear+1)%N;
    return 0;
}
//3.判断队列是否为满
int IsFullSequeue(sequeue_t *p)
{
    return (p->rear+1)%N == p->front;
}
//4.判断队列是否为空
int IsEmptySequeue(sequeue_t *p)
{
    return p->front == p->rear;
}
//5.出队
datatype OutSequeue(sequeue_t *p)
{
    if(IsEmptySequeue(p))
    {
        printf("OutSequeue failed!\n");
        return -1;
    }
    datatype temp = p->data[p->front];
    p->front = (p->front+1)%N;

    return temp;
}
//6.求队列的有效长度
int LengthSequeue(sequeue_t *p)
{
    return (p->rear - p->front + N)%N;
}
//7.清空队列函数
void ClearSequeue(sequeue_t *p)
{
    p->front = 0;
    p->rear = 0;
}

