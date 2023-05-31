#ifndef _MERGE_H_
#define _MERGE_H_

#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct seq
{
	int data[N];
	int last;

}seqlist_t;

seqlist_t *CreatEpList();//创建空顺序表
int InsertSeqlist(seqlist_t *p,int post,int data);
void ShowList(seqlist_t *p);
int IsFullSeqlist(seqlist_t *p);
int IsEpSeqlist(seqlist_t *p);
int SearchDataSeqList(seqlist_t *p,int data);
void OrderMerge(seqlist_t *pa,seqlist_t *pb);
#endif
