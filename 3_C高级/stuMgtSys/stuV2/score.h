#include <stdio.h>
#include <ctype.h>

/****学生结构体***/
struct student
{
    int num;
    float chinese;
    float math;
    float waiyu;
    float average;
};
/****函数声明***/
void Type(struct student *pstu);//成绩录入
void List(struct student *pstu);//输出成绩表
void Averange(struct student *pstu);//平均分
void Sort(struct student *pstu);//按平均分由高到底排序
void Search(struct student *pstu); //查询学生成绩