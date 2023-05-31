#include "linklist.h"

link_node_t *CreatEpLinkList()
{
	link_node_t *h = (link_node_t *)malloc(sizeof(link_node_t));
	if(NULL == h)
	{
		printf("CreatEpLinkList failed!\n");
		return NULL;
	}
	h->next = NULL;
	return h;
}
//插入
int InsertIntoPostLinkList(link_node_t *p,int post,datatype data)
{
	if(post<0 || post>LenghLinkList(p))
	{
		printf("InsertIntoPostLinkList failed!\n");
		return -1;
	}
	//创建新结点
	link_node_t *pnew = (link_node_t *)malloc(sizeof(link_node_t));
	if(NULL == pnew)
	{
		printf("InsertIntoPostLinkList malloc failed!\n");
		return -1;
	}
	//初始化新结点
	pnew->data = data;
	pnew->next = NULL;

	int i;
	for(i=0;i<post;i++) //找到post前一个结点
	{
		p = p->next;
	}
	//插入
	pnew->next = p->next;
	p->next = pnew;

	return 1;

}
//求长度
int LenghLinkList(link_node_t *p)
{
	int len = 0;
	while(p->next != NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}
//遍历打印
void ShowLinkList(link_node_t *p)
{
	while(p->next != NULL)
	{
		p = p->next;
		printf("%d ",p->data);
	}
	printf("\n");
}

//删除post位置数据
int DelePostLinkList(link_node_t *p,int post)
{
	if(post<0 || post>=LenghLinkList(p) || IsEpLinkList(p))
	{
		printf("DelePostLinkList failed!\n");
		return -1;
	}
	int i;
	for(i=0; i<post; i++)
	{
		p = p->next;
	}
	link_list_t pdel = p->next;
	p->next = pdel->next;
	free(pdel);
	pdel = NULL;

}
//判断空
int IsEpLinkList(link_node_t *p)
{
	return p->next == NULL;
}
//逆置
void ReverseLinkList(link_node_t *p)
{
	if(IsEpLinkList(p))
	{
		printf("ReverseLinkList failed!\n");
	}
	link_list_t q = p->next;
	link_list_t t = NULL;

	p->next = NULL;

	while(q != NULL )
	{
		t = q->next;
	
		q->next = p->next;
		p->next = q;
		
		q = t;
	}

}
