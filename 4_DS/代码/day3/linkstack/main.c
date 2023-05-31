#include "linkstack.h"

int main(int argc, const char *argv[])
{
	linkstack_t *top;
	CreateEpLinkStack(&top);

	int i;
	for(i=0; i<=4; i++)
	{
		PushLinkStack(&top,i);
	}

	//求栈长
	printf("LengthLinkStack = %d\n",LengthLinkStack(top));
	//取栈顶元素
	printf("GetTopLinkStack = %d\n",GetTopLinkStack(top));
	ClearLinkStack(&top);
	printf("%d\n",PopLinkStack(&top));
#if 0
	for(i=0; i<=4; i++)
	{
		printf("%d ",PopLinkStack(&top));
	}
	printf("\n");
#endif

	free(top);
	top = NULL;

	return 0;
}
