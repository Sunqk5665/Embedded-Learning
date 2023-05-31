#include "merge.h"

seqlist_t *CreatEpList()
{
	seqlist_t *p = (seqlist_t *)malloc(sizeof(seqlist_t));
	if(NULL == p){
		printf("CreatEpList failed!\n");
	}
	p->last = -1;
	return p;
}

int InsertSeqlist(seqlist_t *p,int post,int data)
{
	int i=0;
	if(post<0 || post>p->last+1 || IsFullSeqlist(p))
	{
		printf("InsertInto failed!\n");
		return 0;
	}
	for(i=p->last;i>=post;i--)
	{
		p->data[i+1] = p->data[i];
	}
	p->data[post] = data;
	p->last++;
	return 0;
}
void ShowList(seqlist_t *p)
{
	int i;
	for(i=0;i<=p->last;i++)
	{
		printf("p[%d] = %d\n",i,p->data[i]);
	}
	putchar(10);
}


int IsFullSeqlist(seqlist_t *p)
{
	return p->last == N-1;

}
//判断顺序表是否为空，
int IsEpSeqlist(seqlist_t *p)
{
	return p->last == -1;
}
//查找制定数据data在顺序表中的位置
int SearchDataSeqList(seqlist_t *p,int data)
{
	if(IsEpSeqlist(p))
	{
		printf("SearchDataSeqList failed!\n");
		return -1;
	}
	int i;
	for(i=0;i<=p->last;i++)
	{
		if(p->data[i] == data)
		{
			return i;
		}
	}
	return -1; //没有查找到data返回-1
}
void OrderMerge(seqlist_t *pa,seqlist_t *pb)
{
	int i=0;
	for(i=0;i<=pb->last;i++)
	{

		if(!(SearchDataSeqList(pa,pb->data[i])))
		{
			InsertSeqlist(pa,pa->last+1,pb->data[i]);
		}
	}
}

// void OrderMerge(seqlist_t *pa,seqlist_t *pb)
// {
// 	int i=0,j=0;
// 	while(1)
// 	{
// 		if(pa->data[i] > pb->data[j])
// 		{
// 			InsertSeqlist(pa,i,pb->data[j]);
// 			i++;
// 			j++;
// 		}
// 		else if(pa->data[i] < pb->data[j])
// 		{
// 			//InsertSeqlist(pa,i+1,pb->data[j]);
// 			i++;
// 			if(i>pa->last)
// 				pa->last++;
// 			//j++;
// 		}
// 		else
// 		{
// 			i++;
// 			j++;
// 		}
// 		//InsertSeqlist();
// 		if(j>pb->last)
// 			break;

// 	}
// }

