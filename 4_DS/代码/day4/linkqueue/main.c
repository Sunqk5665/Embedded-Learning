#include "linkqueue.h"

int main(int argc, const char *argv[])
{
	linkqueue_t *p = CreateEmptyLinkQueue();
	
	InlinkQueue(p,1);
	InlinkQueue(p,2);
	InlinkQueue(p,3);

	printf("Linklist Length=%d\n",LengthLinkQueue(p));

	printf("%d ",OutLinkQueue1(p));
	printf("%d ",OutLinkQueue1(p));
	printf("%d ",OutLinkQueue1(p));

	printf("\n");
#if 1
	free(p->front);
	p->front = NULL;
	free(p);
	p = NULL;
#endif
#if 0
	free(p->rear);
	p->rear = NULL;
	free(p);
	p = NULL;
#endif
	return 0;
}
