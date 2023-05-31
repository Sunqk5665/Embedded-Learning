#include "linklist.h"

//1.创建空的有头单向链表
link_node_t *CreatEpLinkList()
{
    link_node_t *h = (link_node_t *)malloc(sizeof(link_node_t));
    if(NULL == h)
    {
        printf("CreatEpLinkList error!\n");
        return NULL;
    }
    h->next == NULL;
    return h;
}
//2.向单向链表指定位置插入数据
int InsertIntoPostLinkList(link_node_t *p,int post,datatype data)
{
    if(post<0 || post>LengthLinkList(p)){
        printf("InsetIntoPostLinkList failed!\n");
        return -1;
    }
    //创建新结点
    link_node_t *pnew = (link_node_t *)malloc(sizeof(link_node_t));
    if(NULL == pnew){
        printf("InsetIntoPostLinkList pnew malloc failed!\n");
        return -1;
    }
    //初始化新节点成员
    pnew->data = data;
    pnew->next = NULL;
    //遍历到要删除结点的前一结点
    int i;
    for(i=0; i<post; i++){
        p = p->next;
    }
    //把新节点插入到链表中
    pnew->next = p->next;
    p->next = pnew;

    return 1;
}
//3.遍历打印单向链表
void ShowLinkList(link_node_t *p)
{
    while(p->next != NULL)
    {
        p=p->next;
        printf("%d ",p->data);
    }
    putchar(10);
}
//4.求单向链表长度
int LengthLinkList(link_node_t *p)
{
    int len = 0;
    while (p->next != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}
//5.删除单向链表中指定位置的数据
int DeletePostLinkList(link_node_t *p,int post)
{
    if(IsEpLinkLinst(p) || post<0 || post >= LengthLinkList(p))
    {
        printf("DeletePostLinkList failed!\n");
        return -1;
    }
    int i;
    for(i=0; i<post; i++)
    {
        p = p->next;
    }
    link_list_t pdel = p->next; //新建结点，保存被删除结点
    p->next = pdel->next;
    free(pdel);
    pdel = NULL;

    return 1;
}
//6.判断空
int IsEpLinkLinst(link_node_t *p)
{
    return p->next == NULL;
}
//7.修改指定位置的数据 post 被修改的位置 data修改成的数据
int ChangePostLinkList(link_node_t *p,int post,datatype data)
{
    if(post<0 || post>=LengthLinkList(p) || IsEpLinkLinst(p))
    {
        printf("ChangePostLinkList falied!\n");
        return -1;
    }
    int i;
    for(i=0; i<=post; i++)
    {
        p=p->next;
    }
    p->data = data;
    return 1;
}
//8.查找指定数据出现的位置 data被查找的数据 //search 查找
int SearchDataLinkList(link_node_t *p,datatype data)
{
    if(IsEpLinkLinst(p))//链表为空
    {
        printf("SearchDataLinkList failed!\n");
        return -1;
    }
    int i=0;
    while(p->next != NULL)
    {
        p=p->next;
        if(p->data == data)
        {
            return i; //找到返回data下标
        }
        i++;
    }
    printf("Search %d failed!\n",data);
    return -1;
}

//9.转置链表（原地逆置、头插法）
void ReverseLinkList(link_node_t *p)
{
    if(IsEpLinkLinst(p))
    {
        printf("ReverseLinkList failed!\n");
        return;
    }
    link_list_t q = p->next;
    link_list_t t = NULL; //用来保存q的后继节点
    
    p->next = NULL;  //将头节点和后继节点断开

    while(q != NULL) //无头节点单链表循环遍历结束条件
    {
        t = q->next;

        q->next = p->next;
        p->next = q;

        q = t;
    }
}

//10.删除单向链表中出现的指定数据data,即将单向链表中出现的所有data数据删除
int DeleteDataLinkLint(link_node_t *p,datatype data)
{
    if(IsEpLinkLinst(p)){
        printf("DeleteDataLinkLint failed!\n");
        return -1;
    }
    link_list_t pdel = NULL;
    while(p->next != NULL)
    {
        if(p->next->data == data){
            pdel = p->next;
            p->next = pdel->next;

            free(pdel);
            pdel = NULL;
            //printf("ok\n");
        }
        else{
            p = p->next;
        }
    }
    return 0;
}

//11.清空单向链表
void ClearLinkList(link_node_t *p)
{
    link_list_t pdel = NULL;
    while(p->next != NULL)
    {
        pdel = p->next;
        p->next = pdel->next;
        
        free(pdel);
        pdel = NULL;
    }
    if(p->next == NULL){
        printf("LinkList Cleared!\n");
    }
}
