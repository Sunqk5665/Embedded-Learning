#ifndef _SEQUEUE_H_
#define _SEQUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef int datatype;
typedef struct sequeue
{
	datatype data[N];
	int rear;
	int front;
}sequeue_t;

//1.创建一个空队列
sequeue_t *CreateEpSequeue();
//2.入队data
int InSequeue(sequeue_t *p,datatype data);
//3.判断队满
int IsFullSequeue(sequeue_t *p);
//4.判断队空
int IsEpSequeue(sequeue_t *p);
//5.出队
int OutSequeue(sequeue_t *p);
//6.求队列长度
int LengthSequeue(sequeue_t *p);
//7.清空队列
void ClearSequeue(sequeue_t *p);
#endif
