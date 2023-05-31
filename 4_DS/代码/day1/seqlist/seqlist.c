#include "seqlist.h"
//1.创建一个空表，需要将表首地址返回
seqlist_t *CreateEpList()
{
	seqlist_t *p = (seqlist_t *)malloc(sizeof(seqlist_t));
	if(NULL == p)
	{
		printf("CreateEpList failed!\n");
		return NULL;
	}
	p->last = -1;//last始终代表数组中最后一个有效元素的下标
	return p;
}

//2.向顺序表的指定post下标位置插入数据
int InsertInto(seqlist_t *p,int post,int data)
{
	if(post<0 || post>p->last+1 || IsFullSeqlist(p)){
		printf("InsertInto failed!\n");
		return 0;
	}
	int i=0;
	for(i=p->last;i>=post;i--)
	{
		p->data[i+1] = p->data[i];
	}
	p->data[post] = data;
	p->last++; //元素+1
	return 0;
}
//3.遍历顺序表并打印顺序表
void ShowList(seqlist_t *p)
{
	int i=0;
	for(i=0;i<=p->last;i++)
	{
		printf("p[%d] = %d\n",i,p->data[i]);
	}
	putchar(10);
}
//4.判断顺序表是否为满，满返回1，未满返回0
int IsFullSeqlist(seqlist_t *p)
{
	return p->last == N-1;
}
//5.判断顺序表是否为空，
int IsEpSeqlist(seqlist_t *p)
{
	return p->last == -1;
}
//6.删除顺序表post下标处数据
int DeletePostSeqlist(seqlist_t *p,int post)
{
	if(IsEpSeqlist(p) || post<0 || post>p->last)
	{
		printf("DeletePostSeqlist failed!\n");
		return -1;
	}
	int i;
	for(i=post+1;i<=p->last;i++)
	{
		p->data[i-1] = p->data[i];
	}
	// //或者
	// for(i=post; i<p->last; i++)
	// {
	// 	p->data[i] = p->data[i+1];
	// }
	p->last--; //下标-1
	return 0;
}
//7.清空顺序表
void ClearSeqList(seqlist_t *p)
{
	p->last = -1;
}
//8.修改顺序表下标post处的值
int ChangePostSeqlist(seqlist_t *p,int post,int data)
{
	if(post<0 || post>p->last || IsEpSeqlist(p))
	{
		printf("ChangePostSeqlist failed!\n");
		return -1;
	}
	p->data[post] = data;
	return 1;
}
//9.查找制定数据data在顺序表中的位置
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

