#include "seqlist.h"

int main()
{
	seqlist_t *p = CreateEpList();

	InsertInto(p,0,1);
	InsertInto(p,1,2);
	InsertInto(p,2,3);
	ShowList(p);
	
	InsertInto(p,1,100);
	ShowList(p);

	DeletePostSeqlist(p,1);
	ShowList(p);

	ChangePostSeqlist(p,1,200);
	ShowList(p);

	printf("%d\n",SearchDataSeqList(p,3));

	ClearSeqList(p);

	free(p);
	p=NULL;

	return 0;
}
