#include <stdio.h>

int InsertInto(int *p,int n,int post,int data)
{
    int i=0;
    if(post<0 | post>n){
        printf("Insert failed!\n");
        return -1;
    }
    for(i = n-1;i>=post;i--){
        p[i+1]=p[i];
    }
    p[i+1] = data;

    return 1;
}
void Show(int *p,int n)
{
    for(int i=0;i<n;i++){
        printf("%d ",p[i]);
    }
    printf("\n");
}

int main()
{
    int a[32] = {1,2,3,4,5,6,7,8};
    InsertInto(a,8,3,100);
    Show(a,9);

    return 0;
}