#ifndef _BITREE_H_
#define _BITREE_H_
#include <stdio.h>
#include <stdlib.h>

typedef int datatype_tree;
typedef struct bitree_node
{
	datatype_tree data;
	struct bitree_node *lchild;
	struct bitree_node *rchild;
}bitree_node_t,*bitree_list_t;

//创建二叉树结点
bitree_node_t *CreateBitree();
//前序
void PreOrder(bitree_list_t r);
//中序
void InOrder(bitree_list_t r);
//后序
void PostOrder(bitree_list_t r);
//层次
void UnOrder(bitree_list_t r);

#endif

