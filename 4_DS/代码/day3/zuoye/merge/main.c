#include "merge.h"

int main(int argc, const char *argv[])
{
	link_node_t *pa = CreatLinkList();
	link_node_t *pb = CreatLinkList();
	link_node_t *pc = CreatLinkList();
#if 1
	InsertPostLinkList(pa,0,1);
	InsertPostLinkList(pa,1,3);
	InsertPostLinkList(pa,2,5);
	InsertPostLinkList(pa,3,7);
	InsertPostLinkList(pa,4,9);
	InsertPostLinkList(pa,5,10);
	ShowLinkList(pa);

	InsertPostLinkList(pb,0,2);
	InsertPostLinkList(pb,1,4);
	InsertPostLinkList(pb,2,5);
	InsertPostLinkList(pb,3,8);
	InsertPostLinkList(pb,4,11);
	InsertPostLinkList(pb,5,15);
	ShowLinkList(pb);
#endif

#if 1
	MergeAB(pa,pb,pc);
	ShowLinkList(pc);
#endif
	free(pa);
	free(pb);
	free(pc);
	pa = NULL;
	pb = NULL;
	pc = NULL;

	return 0;
}
