#include "merge.h"

//创建有头单链表空结点
link_node_t *CreatLinkList()
{
	link_node_t *h = (link_node_t *)malloc(sizeof(link_node_t));
	if(NULL == h)
	{
		printf("CreatLinkList failed!\n");
		return NULL;
	}
	h->next = NULL;
	return h;
}
//求单链表长度
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
//post位置插入
int InsertPostLinkList(link_node_t *p,int post,int data)
{
	if(post<0 || post>LengthLinkList(p))
	{
		printf("InsertPostLinkList failed!\n");
		return -1;
	}
	link_node_t *pnew = (link_node_t *)malloc(sizeof(link_node_t));
	if(NULL == pnew)
	{
		printf("InsertPostLinkList pnew malloc failed!\n");
		return -1;
	}
	pnew->data = data;
	pnew->next = NULL;

	int i;
	for(i=0; i<post; i++)
	{
		p=p->next;
	}
	//插入
	pnew->next = p->next;
	p->next = pnew;

	return 1;
}
//遍历打印
void ShowLinkList(link_node_t *p)
{
	if(p->next == NULL)
	{
		printf("LinkList is empty now!\n");
		return;
	}
	while(p->next != NULL)
	{
		p = p->next;
		printf("%d ",p->data);
	}
	printf("\n");
}

//合并函数
void MergeAB(link_node_t *pa,link_node_t *pb,link_node_t *pc)
{
	pa=pa->next;
	pb=pb->next;
	while(pa != NULL && pb != NULL)
	{
		if(pa->data < pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;

		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	if(pa == NULL)
	{
		pc->next = pb;
	}
	else
	{
		pc->next = pa;
	}
}

