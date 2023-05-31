#include <stdio.h>
#include <stdlib.h>

struct student
{
    int num;
    float chinese;
    float math;
    float waiyu;
    float average;
};
/****函数声明***/
void Help();//帮助菜单显示函数
void Type(struct student *pstu);//成绩录入
void List(struct student *pstu);//输出成绩表
void Averange(struct student *pstu);//平均分
void Sort(struct student *pstu);//按平均分由高到底排序
void Search(struct student *pstu); //查询学生成绩
void Clear();   //清屏



int flag = 0;
int manNum = 0;//学生数

int main()
{

    char opt;   //命令变量
    //Help();//首次运行显示帮助菜单
    struct student stu[10];


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
            case 'H':Help();break;//显示帮助菜单
            case 'T':Type(stu);break;//成绩录入
            case 'A':Averange(stu);;break;
            case 'L':List(stu);break;//列出成绩表
            case 'P':Sort(stu);break;//按平均成绩由高到低拍排序
            case 'S':Search(stu);break;//按学号查询学生成绩
            case 'C':Clear();break;//清屏
            case 'Q':return 0;break; //退出系统
            default:printf("输入命令有误！\n");break;
        }


    }
    



    return 0;
}

void Help()//帮助菜单显示函数 H
{
    printf("\n");
    for(int i=1;i<=46;i++){
        printf("*");
    }
    printf("\n");
    printf("  *      学生成绩管理系统———帮助菜单       *  \n");
    for(int i=1;i<=46;i++){
        printf("*");
    }
    printf("\n");
    printf("  *         H = 显示帮助菜单               *  \n");
    printf("  *         T = 成绩录入                   *  \n");
    printf("  *         A = 计算学生平均分             *  \n");
    printf("  *         L = 列出成绩表                 *  \n");
    printf("  *         P = 按平均成绩由高到低排序     *  \n");
    printf("  *         S = 按学号查询学生成绩         *  \n");
    printf("  *         C = 清屏                       *  \n");
    printf("  *         Q = 退出系统                   *  \n");
    for(int i=1;i<=46;i++){
        printf("*");
    }
    printf("\n");
    printf("  * Copyright <C> 2023.05.19  By Sunqk5665 *  \n");
    for(int i=1;i<=46;i++){
        printf("*");
    }
    printf("\n");

}
void Type(struct student *pstu)//成绩录入 T
{
    printf("请输入学生人数：");
    scanf("%d",&manNum);
    printf("请输入%d名学生的三门课成绩：\n",manNum);
    printf("学号 语文 数学 外语\n");
    for(int i = 0; i < manNum; i++){
        scanf("%d  %f  %f  %f",&pstu[i].num,&pstu[i].chinese,&pstu[i].math,&pstu[i].waiyu);
        //getchar();
    }
    getchar();//吃最后一次输入后的回车

}
void List(struct student *pstu)//输出成绩表 L
{
    if(manNum == 0){
        printf("成绩为空！请先使用命令 T 录入学生成绩。\n");
        return;//函数到此终止
    }
    printf("学号 语文 数学 外语 平均分\n");
    for(int i=0; i<manNum; i++){
        printf(" %d   %.1f %.1f %.1f %.1f\n",pstu[i].num,pstu[i].chinese,pstu[i].math,pstu[i].waiyu,pstu[i].average);
    }
}
void Averange(struct student *pstu)//平均分 A
{
    if(manNum == 0){
        printf("成绩为空！请先使用命令 T 录入学生成绩。\n");
        return;//函数到此终止
    }
    for(int i=0; i<manNum; i++){
        pstu[i].average = (pstu[i].chinese + pstu[i].math + pstu[i].waiyu)/3;
    }
    printf("平均分已计算完，请使用命令 L 查看。\n");
}
void Sort(struct student *pstu) //按平均分由高到底排序 P
{
    if(manNum == 0){
        printf("成绩为空！请先使用命令 T 录入学生成绩。\n");
        return;//函数到此终止
    }
    struct student stTemp;//交换中转
    for(int i = 1; i < manNum; i++){
        for(int j = 0; j < manNum-i; j++){
            if (pstu[j].average < pstu[j+1].average){
                stTemp = pstu[j];
                pstu[j] = pstu[j+1];
                pstu[j+1] = stTemp;
            }
        }
    }
    printf("完成排序，请使用 L 查看。\n");
}
void Search(struct student *pstu) //按学号查询学生成绩 S
{
    if(manNum == 0){
        printf("成绩为空！请先使用命令 T 录入学生成绩。\n");
        return;//函数到此终止
    }
    int stuNum;

    printf("亲输入要查询的学生学号：");
    scanf("%d",&stuNum);
    if(stuNum <= 0 && stuNum >=manNum){
        printf("输入学号有误！\n");
    }
    getchar();
    for(int i=0; i<manNum; i++){
        if(pstu[i].num == stuNum){
            printf("学号 语文 数学 外语 平均分\n");
            printf(" %d   %.1f %.1f %.1f %.1f\n",pstu[i].num,pstu[i].chinese,pstu[i].math,pstu[i].waiyu,pstu[i].average);
        }
    }   

}
void Clear()//清屏 C
{
    system("clear"); //"clear"为Linux终端清屏命令（实质是向上翻页）
}

