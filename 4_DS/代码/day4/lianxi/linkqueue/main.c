#include "linkqueue.h"

int main(int argc, const char *argv[])
{
	linkqueue_t *p = CreateLinkQueue();

	int i;
	for(i=0; i<4;i++)
	{
		InLinkQueue(p,i);
	}

	printf("LinkQueue Length=%d\n",LengthLinkQueue(p));

	for(i=0; i<4; i++)
	{
		printf("%d ",OutLinkQueue(p));
	}
	printf("\n");

	return 0;
}
