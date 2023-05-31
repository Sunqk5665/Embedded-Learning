#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node_t
{
	datatype data;
	struct node_t *next;
}link_node_t,*link_list_t;

//创建
link_node_t *CreatEpLinkList();
//插入
int InsertIntoPostLinkList(link_node_t *p,int post,datatype data);
//遍历打印
void ShowLinkList(link_node_t *p);
int LenghLinkList(link_node_t *p);
int DelePostLinkList(link_node_t *p,int post);
//判空
int IsEpLinkList(link_node_t *p);
//逆置
void ReverseLinkList(link_node_t *p);
#endif
