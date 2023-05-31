#include "merge.h"

int main(int argc, const char *argv[])
{
	seqlist_t *pa = CreatEpList();
	seqlist_t *pb = CreatEpList();

	InsertSeqlist(pa,0,1);
	InsertSeqlist(pa,1,3);
	InsertSeqlist(pa,2,5);
	InsertSeqlist(pa,3,7);
	ShowList(pa);
	
	InsertSeqlist(pb,0,5);
	InsertSeqlist(pb,1,7);
	InsertSeqlist(pb,2,9);
	InsertSeqlist(pb,3,11);
	ShowList(pb);

	OrderMerge(pa,pb);
	ShowList(pa);

	free(pa);
	pa = NULL;
	free(pb);
	pb = NULL;
	return 0;
}
