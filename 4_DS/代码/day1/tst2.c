#include <stdio.h>

int last = 6;//全局,表示下标

int InsertInto(int *p,int post,int data)
{
    int i=0;
    if(post<0 || post>last+1)
    {
        printf("Insert failed!\n");
        return 0;
    }
    for(i = last; i>=post;i--){
        p[i+1]=p[i];
    }
    p[post] = data;
    last++;

    return 1;
}
void Show(int *p)
{
    for(int i=0; i<=last; i++){
        printf("a[%d] = %d\n",i,p[i]);
    }
    printf("\n");
}

int main(int argc,char *argv[])
{
    int a[32] = {1,2,3,4,5,6,7};
    InsertInto(a,3,100);
    Show(a);

    return 0;
}