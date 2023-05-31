#include "bitree.h"

int main(int argc, const char *argv[])
{
	bitree_node_t *r = CreateBitree(3,1);

	PreOrder(r);
	printf("\n");

	InOrder(r);
	printf("\n");

	PostOrder(r);
	printf("\n");
	return 0;
}
