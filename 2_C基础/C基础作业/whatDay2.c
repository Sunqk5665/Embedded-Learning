#include <stdio.h>

int main()
{
    int year, mon, day, sum;
    int sumMon=0;//前面 mon-1 个月的天数
    int flag = 0;//润年平年标志
    printf("请输入年月日（例如：2023 5 4）：\n");
    scanf("%d %d %d",&year,&mon,&day);
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        flag = 1;
    else
        flag = 0;
    
    switch (mon)
    {
        case 12:sumMon += 30;    //若是12月xx日，加上11~1月天数
        case 11:sumMon += 31;    //若是11月xx日，加上10~1月天数
        case 10:sumMon += 30;    //若是10月xx日，加上9~1月天数
        case 9:sumMon += 31;     //若是9月xx日，加上8~1月天数
        case 8:sumMon += 31;     //若是8月xx日，加上7~1月天数
        case 7:sumMon += 30;     //若是7月xx日，加上6~1月天数
        case 6:sumMon += 31;     //若是6月xx日，加上5~1月天数
        case 5:sumMon += 30;     //若是5月xx日，加上4~1月天数
        case 4:sumMon += 31;     //若是4月xx日，加上3~1月天数
        case 3:sumMon += (flag==1?29:28);//若是3月xx日，加上2~1月天数
        case 2:sumMon += 31;     //若是2月xx日，加上1月天数
        case 1:sumMon += 0;break;     //若是1月xx日，加0
        default:printf("月份错误！\n");break;
    }

    sum = sumMon + day;
    printf("这是%d年的第%d天\n",year,sum);
    return 0;
}