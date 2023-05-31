#include "sequeue.h"

int main(int argc, const char *argv[])
{
	sequeue_t *p = CreateEpSequeue();
	int i;
	for(i=0; i<4; i++)
	{
		InSequeue(p,i);
	}
	printf("Sequeue Length = %d\n",LengthSequeue(p));
	for(i=0; i<4; i++)
	{
		printf("%d ",OutSequeue(p));
	}
	printf("\n");

	if(IsEpSequeue(p))
	{
		printf("Sequeue is Empty!\n");
	}
	for(i=0; i<4; i++)
	{
		InSequeue(p,i);
	}

	ClearSequeue(p);
	if(IsEpSequeue(p))
	{
		printf("Sequeue is Empty!\n");
	}
	free(p);
	p = NULL;
	return 0;
}
