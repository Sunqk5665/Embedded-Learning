#include "linklist.h"

int main(int argc, const char *argv[])
{
	link_node_t *p = CreatEpLinkList();
	InsertIntoPostLinkList(p,0,10);
	InsertIntoPostLinkList(p,1,20);
	InsertIntoPostLinkList(p,2,30);
	InsertIntoPostLinkList(p,3,40);
	ShowLinkList(p);
	
	DelePostLinkList(p,2);
	ShowLinkList(p);

	ReverseLinkList(p);
	ShowLinkList(p);


	return 0;
}
