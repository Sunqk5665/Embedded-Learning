#include "linklist.h"

int main(int argc, const char *argv[])
{
	link_node_t *p = CreatEpLinkList();
	
	InsertPostLinkList(p,0,10);
	InsertPostLinkList(p,1,20);
	InsertPostLinkList(p,2,30);
	InsertPostLinkList(p,3,40);
	ShowLinkList(p);
	
	DeletePostLinkList(p,1);
	ShowLinkList(p);

	ReverseLinkList(p);
	ShowLinkList(p);

	return 0;
}
