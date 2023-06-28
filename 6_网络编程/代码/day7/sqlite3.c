#include <stdio.h>
#include <sqlite3.h>

int callback(void *arg, int f_num, char **f_value, char **f_name) //回调函数
{
    //select每找到一条记录自动执行一次回调函数
    printf("srg:%s \n", (char *)arg); //打印一下传过来的参数(目的是查看回调函数执行了几次)
    for (int i = 0; i < f_num; i++)
    {
        printf("%s ", f_name[i]);
    }
    putchar(10);
    for (int i = 0; i < f_num; i++)
    {
        printf("%s ", f_value[i]);
    }
    putchar(10);
    return 0;
}
int main(int argc, char const *argv[])
{
    sqlite3 *db = NULL;
    //1.打开或创建数据库
    if (sqlite3_open("./stu.db", &db) != 0)
    {
        fprintf(stderr, "sqlite3_open err:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    //2.创建表
    char *errmsg = NULL;
    if (sqlite3_exec(db, "create table stu1(id int,name char,score float);", NULL, NULL, &errmsg) != 0)
    {
        fprintf(stderr, "create err:%s\n", errmsg);
        // return -1;//表
    }
    //3.向表中插入数据
    // int n, id;
    // char name[32];
    // float score;
    // char sql[128]; //存放sql语句
    // printf("please input student number:");
    // scanf("%d", &n); //要插入数据的条数
    // for (int i = 0; i < n; i++)
    // {
    //     scanf("%d %s %f", &id, name, &score);
    //     sprintf(sql, "insert into stu1 values(%d,\"%s\",%f);", id, name, score);
    //     printf("sql:%s\n", sql);
    //     if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
    //     {
    //         fprintf(stderr, "insert err:%s", errmsg);
    //         return -1;
    //     }
    // }

    // //4.查询（一）
    // if (sqlite3_exec(db, "select * from stu1;", callback, "hello", &errmsg) != 0)
    // {
    //     fprintf(stderr, "select err:%s", errmsg);
    //     return -1;
    // }
    //查询（二）
    char **result = NULL; //用来指向sql执行结果的指针
    int hang, lie;
    if (sqlite3_get_table(db, "select * from stu1;", &result, &hang, &lie, &errmsg) != 0)
    {
        fprintf(stderr, "select err:%s", errmsg);
        return -1;
    }
    int k = 0;
    printf("hang:%d lie:%d\n", hang, lie);
    for (int i = 0; i < hang + 1; i++)
    {
        for (int j = 0; j < lie; j++)
        {
            printf("%s ", result[k++]);
        }
        putchar(10);
    }
    //5.关闭数据库
    sqlite3_close(db);
    return 0;
}
