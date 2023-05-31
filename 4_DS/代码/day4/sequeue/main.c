#include "sequeue.h"

int main(int argc, const char *argv[])
{
	sequeue_t *p = CreateEmptySequeue();

	InSequeue(p,1);
	InSequeue(p,2);
	OutSequeue(p);
	InSequeue(p,3);
	InSequeue(p,4);
	
	printf("Sequeue lengh=%d\n",LengthSequeue(p));

	printf("%d ",OutSequeue(p));
	printf("%d ",OutSequeue(p));
	printf("%d ",OutSequeue(p));
//	printf("%d ",OutSequeue(p));
	printf("\n");

	ClearSequeue(p);
	printf("Sequeue lengh=%d\n",LengthSequeue(p));
	
	free(p);
	p = NULL;

	return 0;
}
