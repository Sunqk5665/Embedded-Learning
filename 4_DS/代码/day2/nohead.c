#include <stdio.h>

typedef struct node_t
{
    char data;
    struct node_t *next;
}link_node_t,*link_list_t;

int main()
{
    link_node_t A = {'A',NULL};
    link_node_t B = {'B',NULL};
    link_node_t C = {'C',NULL};
    link_node_t D = {'D',NULL};
    A.next = &B;
    B.next = &C;
    C.next = &D;
    D.next = NULL;

    link_list_t p = &A;

    while(p != NULL)//无头单向链表的变量条件
    {
        printf("%c ",p->data);
        p=p->next;
    }
    putchar(10);

    return 0;
}