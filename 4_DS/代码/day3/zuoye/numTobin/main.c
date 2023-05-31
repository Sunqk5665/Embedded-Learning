#include "tobin.h"

int main(int argc, char const *argv[])
{
    //建栈
    linkstack_t *top;
	CreateEpLinkStack(&top);

    int num;
    int yushu, count = 0;
    printf("请输入要转换的十进制：");
    scanf("%d",&num);
    
    while (num != 0)
    {
        yushu = num % 2;
        PushLinkStack(&top,yushu);
        count++;
        num = num / 2;
    }
    int i;
    for(i=1; i<=count; i++)
    {
        printf("%d ",PopLinkStack(&top));
    }
    printf("\n");
    return 0;
}
