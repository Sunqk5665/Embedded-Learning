#ifndef _TOBIN_
#define _TOBIN_
#include <stdio.h>
#include <stdlib.h>
typedef int datatype;

typedef struct linkstack
{
	datatype data;
	struct linkstack *next;
}linkstack_t;
//创建一个空的栈
void CreateEpLinkStack(linkstack_t **ptop);
//入栈
int PushLinkStack(linkstack_t **ptop,datatype data);
//判断栈是否为空
int IsEpLinkStack(linkstack_t *top);
//出栈
datatype PopLinkStack(linkstack_t **ptop);

#endif
