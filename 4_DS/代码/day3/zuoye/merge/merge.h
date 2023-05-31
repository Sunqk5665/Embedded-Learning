#ifndef _MERGE_H_
#define _MERGE_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct linknode
{
	int data;
	struct linknode *next;
}link_node_t,*link_list_t;

//创建有头单链表空结点
link_node_t *CreatLinkList();
//合并函数
void MergeAB(link_node_t *pa,link_node_t *pb,link_node_t *pc);
//求单链表长度
int LengthLinkList(link_node_t *p);
//post位置插入
int InsertPostLinkList(link_node_t *p,int post,int data);

//遍历打印
void ShowLinkList(link_node_t *p);

#endif
