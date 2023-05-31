#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct sqlist
{
	datatype data;
	struct sqlist *next;
}link_node_t,*link_list_t;

//建带头节点空表
link_node_t *CreatEpLinkList();
//求长度
int LengthLinkList(link_node_t *p);
//post处插入数据
int InsertPostLinkList(link_node_t *p,int post,datatype data);
//判空
int IsEpLinkList(link_node_t *p);
//删除post处数据
int DeleteLinkList(link_node_t *p,int post);
//逆置
void ReverseLinkList(link_node_t *p);
//遍历打印
void ShowLinkList(link_node_t *p);

#endif
