#include "seqstack.h"

//1.创建一个空的栈
seqstack_t *CreateEpSeqStack(int len)
{
	seqstack_t *p = (seqstack_t *)malloc(sizeof(seqstack_t));
	if(NULL == p){
		printf("malloc seqstack_t error\n");
		return NULL;
	}
	//申请存放数据的空间
	p->data = (int *)malloc(sizeof(int)*len);
	if(NULL == p->data){
		printf("malloc p->data error!\n");
		return NULL;
	}
	//p指向的成员初始化
	p->maxlen = len;
	p->top = -1;

	return p;	
}

//2.判断是否为满，满返回1,未满返回0
int IsFullSeqStack(seqstack_t *p)
{
	return p->top == p->maxlen-1;
}
//4.判断栈是否空
int IsEpSeqStack(seqstack_t *p)
{
	return p->top == -1;
}
//3.入栈
int PushStack(seqstack_t *p,int data)
{
	if(IsFullSeqStack(p))
	{
		printf("PushStack failed!\n");
		return -1;
	}
	p->top++;
	p->data[p->top] = data;
	return 0;

}
//5.出栈
int PopSeqStack(seqstack_t *p)
{
	if(IsEpSeqStack(p))
	{
		printf("PopSeqStack failed!\n");
		return -1;
	}
	return p->data[p->top--];
}

//6.清空栈
void ClearSeqStack(seqstack_t *p)
{
	p->top = -1;
}
//7.获取栈顶数据（只是获取）
int GetTopSeqStack(seqstack_t *p)
{
	return p->data[p->top];
}
//8.求栈长度
int LengthSeqStack(seqstack_t *p)
{
	return p->top+1;
}
