#include "score.h"
extern int manNum;

void Type(struct student *pstu)//成绩录入 T
{
    printf("请输入学生人数：");
    scanf("%d",&manNum);
    printf("请输入%d名学生的三门课成绩：\n",manNum);
    printf("学号 语文 数学 外语\n");

    for(int i = 0; i < manNum; i++){
        pstu[i].num = i+1;
        printf("%d   ",pstu[i].num);
        scanf("%f  %f  %f",&pstu[i].chinese,&pstu[i].math,&pstu[i].waiyu);
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

    printf("请输入要查询的学生学号：");
    scanf("%d",&stuNum);
    getchar();
    if(stuNum>0 && stuNum<=manNum){
        for(int i=0; i<manNum; i++){
            if(pstu[i].num == stuNum){
                printf("学号 语文 数学 外语 平均分\n");
                printf(" %d   %.1f %.1f %.1f %.1f\n",pstu[i].num,pstu[i].chinese,pstu[i].math,pstu[i].waiyu,pstu[i].average);
            }
        }
    }
    else{
        printf("输入的学号非法，请仔细核对！！\n");
    }
}