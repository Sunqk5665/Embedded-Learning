/**********2023/05/26约瑟夫问题*********/
#include <stdio.h>
#include <stdlib.h>

typedef struct circlelink //定义循环链表结构体
{
    int data;
    struct circlelink *next;
}link_node_t,*link_list_t;


int main(int argc,char *argv[])
{
    int all_num = 6;
    int start_num = 1;//开始报数的号码
    int kill_num = 5;

    printf(">>请输入总人数：");
    scanf("%d",&all_num);
    putchar(10);
    printf(">>请输入首次报数的号码：");
    scanf("%d",&start_num);
    putchar(10);
    printf(">>请输入报数到多少：");
    scanf("%d",&kill_num);
    putchar(10);

    link_node_t *h = (link_list_t)malloc(sizeof(link_node_t));//创建头节点
    if(NULL == h)
    {
        printf("malloc head failed!\n");
        return -1;
    }
    h->data = 1;
    h->next = NULL;
    link_node_t *ptail = h;

    int i;
    for(i=2; i<=all_num; i++)//创建循环链表，同时赋值
    {
        link_node_t *pnew = (link_list_t)malloc(sizeof(link_node_t));
        pnew->data = i;
        pnew->next = NULL;
        
        ptail->next = pnew;
        ptail = pnew;
    }
    ptail->next = h;//尾结点指向头，完成循环链表的创建。。。


    link_node_t *p = h;//要i循环遍历的指针变量


    for(int i=1; i<=start_num-1; i++)//找到开始报数的人
    {
        p=p->next;
    }

    while(p->next != p)//循环杀死报数为kill_num的人
    {
        for(int i=1; i<=kill_num-2; i++)//找到要杀死的前一个
        {
            p=p->next;
        }

        link_node_t *pdel = p->next;
        p->next = pdel->next;
        free(pdel);
        pdel = NULL;

        p=p->next;//移动到已杀死进程的下一结点

    }
    printf(">>The king is %d 号\n",p->data);
    
    free(p);
    p = NULL;

    return 0;
}