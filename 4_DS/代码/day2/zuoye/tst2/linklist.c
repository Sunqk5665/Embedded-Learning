#include "linklist.h"

link_node_t *CreatEpLinkList()
{
	link_node_t *h = (link_list_t)malloc(sizeof(link_node_t));
	if(NULL == h)
	{
		printf("CreatEpLinkList malloc failed!\n");
		return NULL;
	}
	h->next = NULL;
	return h;
}
//post处插入数据
int InsertPostLinkList(link_node_t *p,int post,datatype data)
{
	if(post<0 || post>LengthLinkList(p))
	{
		printf("InsertPostLinkList failed!\n");
		return -1;
	}
	link_node_t *pnew = (link_list_t)malloc(sizeof(link_node_t));
	if(NULL == pnew)
	{
		printf("InsertPostLinkList malloc ffailed!\n");
		return -1;
	}
	//初始化结点成员
	pnew->data = data;
	pnew->next = NULL;

	int i;
	for(i=0; i<post; i++)//找到post前一个结点
	{
		p=p->next;
	}
	pnew->next = p->next;
	p->next = pnew;
	
	return 1;

}
//求长度
int LengthLinkList(link_node_t *p)
{
	int len = 0;
	while(p->next != NULL)
	{
		p=p->next;
		len++;
	}
	return len;
}
//判空
int IsEpLinkList(link_node_t *p)
{
	return p->next == NULL;
}

//删除post处的位置
int DeletePostLinkList(link_node_t *p,int post)
{
	if(post<0 || post>=LengthLinkList(p) || IsEpLinkList(p))
	{
		printf("DeletePostLinkList failed!\n");
		return -1;
	}
	int i;
	for(i=0; i<post; i++)
	{
		p=p->next;
	}
	link_node_t *pdel = p->next;
	p->next = pdel->next;
	free(pdel);
	pdel = NULL;
	return 1;
}

//逆置
void ReverseLinkList(link_node_t *p)
{
	if(IsEpLinkList(p))
	{
		printf("ReverseLinkList failed!\n");
	}
	link_node_t *q = p->next;
	link_node_t *t = NULL;
	p->next = NULL;

	while(q != NULL)
	{
		t = q->next;//t保存q的后继结点
		q->next = p->next;
		p->next = q;
		q = t;
	}
}
//遍历打印
void ShowLinkList(link_node_t *p)
{
	while(p->next != NULL)
	{
		p=p->next;
		printf("%d ",p->data);
	}
	printf("\n");
}

