#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_
#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct linkstack
{
	datatype data;
	struct linkstack *next;
}linkstack_t;
//1.创建一个空的栈
void CreateEpLinkStack(linkstack_t **ptop);
//2.入栈
int PushLinkStack(linkstack_t **ptop,datatype data);
//3.判断栈是否为空
int IsEpLinkStack(linkstack_t *top);
//4.出栈
datatype PopLinkStack(linkstack_t **ptop);
//5.清空栈
void ClearLinkStack(linkstack_t **ptop);
//6.求栈的长度
int LengthLinkStack(linkstack_t *top);
//7.获取栈顶数据（只是获取数据）
datatype GetTopLinkStack(linkstack_t *top);

#endif
