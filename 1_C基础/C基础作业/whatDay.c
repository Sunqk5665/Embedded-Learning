#include <stdio.h>

int main()
{
    int year, mon, day;
    int flag = 0;
    int i,sumMonDay = 0,sum = 0;

    int monArry[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    printf("请输入年月日（例如：2023 5 4）：\n");
    scanf("%d %d %d",&year,&mon,&day);

    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        flag = 1;//润年标志
    else
        flag = 0;//平年标志
    if(flag){
        monArry[2] += 1;
    }
    for(i = 1;i < mon;i++){
        sumMonDay += monArry[i];
    }

    sum = sumMonDay + day;
    printf("这是%d年的第%d天\n",year,sum);

    return 0;
}