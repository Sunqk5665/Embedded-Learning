#ifndef _LINK_H_
#define _LINK_H_
#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct linknode
{
    datatype data;
    struct linknode *next;
}link_node_t,*link_list_t;

//1.创建空的有头单向链表
link_node_t *CreatEpLinkList();
//2.向单向链表指定位置插入数据
int InsertIntoPostLinkList(link_node_t *p,int post,datatype data);
//3.遍历单向链表
void ShowLinkList(link_node_t *p);
//4.求单向链表长度
int LengthLinkList(link_node_t *p);
//5.删除单向链表中指定位置post的数据
int DeletePostLinkList(link_node_t *p,int post);
//6.判断空
int IsEpLinkLinst(link_node_t *p);
//7.修改指定位置的数据 post 被修改的位置 data修改成的数据
int ChangePostLinkList(link_node_t *p,int post,datatype data);
//8.查找指定数据出现的位置 data被查找的数据 //search 查找
int SearchDataLinkList(link_node_t *p,datatype data);
//9.转置链表
void ReverseLinkList(link_node_t *p);
//10.删除单向链表中出现的指定数据,data代表将单向链表中出现的所有data数据删除
int DeleteDataLinkLint(link_node_t *p,datatype data);
//11.清空单向链表
void ClearLinkList(link_node_t *p);


#endif