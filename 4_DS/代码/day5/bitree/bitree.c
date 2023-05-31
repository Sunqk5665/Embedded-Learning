#include "bitree.h"

//创建有n个节点的二叉树(递归创建)
bitree_node_t *CreateBitree(int n, int i)
{
	bitree_list_t r = (bitree_list_t)malloc(sizeof(bitree_node_t));
	if(NULL == r){
		printf("CreateBitree malloc root failed!\n");
		return NULL;
	}
	r->data = i;
	if(2*i <= n){ //判断是否有左子树
		r->lchild = CreateBitree(n,2*i);
	}
	else //若没有左子树
	{
		r->lchild = NULL;
	}
	if(2*i+1 <= n)  //判断是否有右子树
	{
		r->rchild = CreateBitree(n,2*i+1);
	}
	else  //若没有右子树
	{
		r->rchild = NULL;
	}
	return r;
}
//前序
void PreOrder(bitree_list_t r)
{
	if(NULL == r)
		return;
	printf("%d ",r->data);
	if(r->lchild != NULL)
		PreOrder(r->lchild);
	if(r->rchild != NULL)
		PreOrder(r->rchild);
}
//中序
void InOrder(bitree_list_t r)
{
	if(NULL == r)
		return;
	if(r->lchild != NULL)
		InOrder(r->lchild);
	printf("%d ",r->data);
	if(r->rchild != NULL)
		InOrder(r->rchild);
}
//后序
void PostOrder(bitree_list_t r)
{
	if(NULL == r)
		return;
	if(r->lchild != NULL)
		PostOrder(r->lchild);
	if(r->rchild != NULL)
		PostOrder(r->rchild);
	printf("%d ",r->data);
}
//层次
//void UnOrder(bitree_list_t r);
