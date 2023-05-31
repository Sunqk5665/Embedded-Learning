#include "seqstack.h"

int main(int argc, const char *argv[])
{
	seqstack_t *p = CreateEpSeqStack(10);
	int i;
	printf("入栈元素依次为:");
	for(i=0; i<5; i++)//循环入栈
	{
		PushStack(p,i);
		printf("%d ",i);
	}
	printf("\n");
	//获取栈顶数据
	printf("栈顶元素为：%d\n",GetTopSeqStack(p));
	//求栈有效长度
	printf("LengthSeqStack = %d\n",LengthSeqStack(p));
	printf("出栈元素依次为：");
	for(i=0; i<5; i++)
	{
		printf("%d ",PopSeqStack(p));
	}
	printf("\n");

	free(p->data);
	p->data = NULL;
	free(p);
	p = NULL;

	return 0;
}
