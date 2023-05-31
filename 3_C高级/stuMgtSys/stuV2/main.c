#include <stdio.h>
#include <stdlib.h>
#include "help.h"
#include "score.h"
#include "clear.h"


// int flag = 0;
int manNum = 0;//学生数
struct student stu[20]; //结构体数组定义

int main()
{
    char opt;   //命令
    Help(); //首次运行显示帮助菜单
    while (1)
    {
        printf("\n");
        printf("请输入命令=");
        if(scanf("%c",&opt)){
            //printf("scanf出现EOF错误！\n");
            getchar();//吃掉空格
        }
        switch (opt)
        {
            case 'H':Help();break;           //显示帮助菜单
            case 'T':Type(stu);break;        //成绩录入
            case 'A':Averange(stu);;break;   //计算平均分
            case 'L':List(stu);break;        //列出成绩表
            case 'P':Sort(stu);break;        //按平均成绩由高到低拍排序
            case 'S':Search(stu);break;      //按学号查询学生成绩
            case 'C':Clear();break;          //清屏
            case 'Q':return 0;break;         //退出系统
            default:
                printf("输入命令有误！\n");break;
        }

    }
    return 0;
}

