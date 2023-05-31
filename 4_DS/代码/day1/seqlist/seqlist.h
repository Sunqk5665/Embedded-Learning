#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct seqlist
{
	int data[N];
	int last;  //数组中最后一个有效元素的下标
}seqlist_t;


//1.创建一个空表，需要将表首地址返回
seqlist_t *CreateEpList();
//2.向顺序表的指定post下标位置插入数据
int InsertInto(seqlist_t *p,int post,int data);
//3.遍历顺序表并打印顺序表
void ShowList(seqlist_t *p);
//4.判断顺序表是否为满，满返回1，未满返回0
int IsFullSeqlist(seqlist_t *p);
//5.判断顺序表是否为空，
int IsEpSeqlist(seqlist_t *p);
//6.删除顺序表post下标处数据
int DeletePostSeqlist(seqlist_t *p,int post);
//7.清空顺序表
void ClearSeqList(seqlist_t *p);、
//8.修改顺序表post下标处的值
int ChangePostSeqlist(seqlist_t *p,int post,int data);
//9.查找制定数据data在顺序表中的位置
int SearchDataSeqList(seqlist_t *p,int data);



#endif
