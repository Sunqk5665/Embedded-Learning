#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct seqstack
{
	int *data;  //指向栈元素的存储位置
	int maxlen; //保存栈的最大长度
	int top;    //栈顶
}seqstack_t;
//1.创建一个空的栈
seqstack_t *CreateEpSeqStack(int len);//len为创建栈的最大长度
//2.判断是否为满，满返回1,未满返回0
int IsFullSeqStack(seqstack_t *p);
//3.入栈
int PushStack(seqstack_t *p,int data);
//4.判断栈是否空
int IsEpSeqStack(seqstack_t *p);
//5.出栈
int PopSeqStack(seqstack_t *p);
//6.清空栈
void ClearSeqStack(seqstack_t *p);
//7.获取栈顶数据（只是获取）
int GetTopSeqStack(seqstack_t *p);
//8.求栈有效长度
int LengthSeqStack(seqstack_t *p);

#endif
