#include "tobin.h"

//创建一个空的栈
void CreateEpLinkStack(linkstack_t **ptop)
{
	*ptop = NULL;
}
//入栈
int PushLinkStack(linkstack_t **ptop,datatype data)
{
	linkstack_t *pnew = (linkstack_t *)malloc(sizeof(linkstack_t));
	if(NULL == pnew)
	{
		printf("PushLinkStack malloc failed!\n");
		return -1;
	}
	//新结点初始化
	pnew->data = data;
	pnew->next = NULL;
	//新节点放到栈顶
	pnew->next = *ptop;
	*ptop = pnew;

	return 0;
}
//判断栈是否为空
int IsEpLinkStack(linkstack_t *top)
{
	return top == NULL; 
}
//出栈
datatype PopLinkStack(linkstack_t **ptop)
{
	if(IsEpLinkStack(*ptop))
	{
		printf("PopLinkStack failed!");
		return -1;
	}
	datatype temp;
	linkstack_t *pdel = NULL;

	pdel = *ptop;
	*ptop = pdel->next;
	temp = pdel->data;
	free(pdel);
	pdel = NULL;
	return temp;
}
