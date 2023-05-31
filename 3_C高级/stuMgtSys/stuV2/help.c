#include "help.h"

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
    printf("  *   Copyright <C> 2023.05.19 By 孙启凯   *  \n");
    for(int i=1;i<=46;i++){
        printf("*");
    }
    printf("\n");
}