#include "head.h"

//注册
void do_register(int acceptfd, MSG_t msg, sqlite3 *db);
//登录
void do_login(int acceptfd, MSG_t msg, sqlite3 *db);
//退出
void do_quit(int acceptfd, MSG_t msg);
//查询单词
void do_query(int acceptfd, MSG_t msg, sqlite3 *db);
//历史
void do_history(int acceptfd, MSG_t msg, sqlite3 *db);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Please input:%s <port>\n", argv[0]);
        return 0;
    }
    //打开数据库
    sqlite3 *db = NULL;
    if (sqlite3_open("./data.db", &db) != 0)
    {
        fprintf(stderr, "sqlite3_open err:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    char *errmsg = NULL;
    //在数据库中创建用户信息表，注册登录使用
    if (sqlite3_exec(db, "create table users(name char primary key,password char);", NULL, NULL, &errmsg) != 0)
    {
        fprintf(stderr, "create err:%s\n", errmsg);
        //return -1;
    }
    //在数据库中创建历史记录表，用于查询历史记录
    if (sqlite3_exec(db, "create table history(name char,word char,time char);", NULL, NULL, &errmsg) != 0)
    {
        fprintf(stderr, "create err:%s\n", errmsg);
    }
    //创建套接字
    int sockfd, acceptfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    printf("sockfd=%d\n", sockfd);
    printf("socket ok...\n");
    //填充IPV4通信结构体
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;            //ipv4
    saddr.sin_port = htons(atoi(argv[1])); //端口
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    //绑定套接字
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    printf("bind ok...\n");
    //监听
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok...\n");

    socklen_t len = sizeof(caddr);
    while (1)
    {
        //accept，阻塞等待客户端链接，成功返回一个新的通信描述符
        acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
        if (acceptfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        //获取到请求链接服务器的客户端的ip和端口
        printf("acceptfd=%d\n", acceptfd);
        printf("client ip=%s port=%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

        MSG_t msg;

        pid_t pid = fork(); //创建子进程
        if (pid < 0)
        {
            perror("fork err.");
            return -1;
        }
        else if (pid == 0) //子进程接收消息
        {
            //循环接收消息 recv
            int recvbyte;
            // char buf[128];
            while (1)
            {
                recvbyte = recv(acceptfd, &msg, sizeof(msg), 0);
                if (recvbyte < 0)
                {
                    perror("recv err.");
                    return -1;
                }
                else if (recvbyte == 0)
                {
                    printf("client exit...\n");
                    break;
                }
                else
                {
                    switch (msg.type)
                    {
                    case regist:
                        do_register(acceptfd, msg, db);
                        break;
                    case login:
                        do_login(acceptfd, msg, db);
                        break;
                    case quit:
                        do_quit(acceptfd, msg);
                        break;
                    case query:
                        do_query(acceptfd, msg, db);
                        break;
                    case history:
                        do_history(acceptfd, msg, db);
                        break;
                    default:
                        break;
                    }
                }
            }
            close(acceptfd);
        }
        else //父进程发送消息
        {
        }
    }
    close(sockfd);
    return 0;
}

//注册
void do_register(int acceptfd, MSG_t msg, sqlite3 *db)
{
    char sql[128]; //存放sql语句
    char *errmsg = NULL;

    sprintf(sql, "insert into users values(\"%s\",\"%s\");", msg.name, msg.data);
    //printf("sql:%s\n", sql);
    if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
    {
        printf("user is exist!\n");
        sprintf(msg.data, "user %s alreday exist", msg.name);
        fprintf(stderr, "insert err:%s\n", errmsg);
        // return; //怪不得，大意了！！
    }
    else
    {
        strcpy(msg.data, "regist ok...");
    }
    if (send(acceptfd, &msg, sizeof(msg), 0) < 0) //发送
    {
        perror("send err.");
        return;
    }
}
//登录
void do_login(int acceptfd, MSG_t msg, sqlite3 *db)
{
    char **resultp = NULL;
    int nrow, ncolumn;
    char *errmsg;
    char sql[128];
    sprintf(sql, "select * from users where name='%s' and password='%s';", msg.name, msg.data);
    if (sqlite3_get_table(db, sql, &resultp, &nrow, &ncolumn, &errmsg) != 0)
    {
        fprintf(stderr, "select err:%s\n", errmsg);
        return;
    }
    if (nrow == 0) //没有查询到用户信息
    {
        strcpy(msg.data, "name or password err");
    }
    else //查到了数据
    {
        strcpy(msg.data, "login ok...");
    }
    if (send(acceptfd, &msg, sizeof(MSG_t), 0) < 0) //消息发送
    {
        perror("send err");
        return;
    }
    return;
}
//退出
void do_quit(int acceptfd, MSG_t msg)
{
    if (msg.type = quit)
    {
        printf("exit...\n");
    }
    return;
}
//查询单词
void do_query(int acceptfd, MSG_t msg, sqlite3 *db)
{
    char date[128]; //存时间
    char **resultp = NULL;
    int nrow, ncolumn;
    char *errmsg;
    char sql[128];
    sprintf(sql, "select * from dict where word='%s';", msg.data);
    if (sqlite3_get_table(db, sql, &resultp, &nrow, &ncolumn, &errmsg) != 0)
    {
        fprintf(stderr, "select err:%s\n", errmsg);
        return;
    }
    // printf("%d %d\n",nrow,ncolumn);
    if (nrow == 0) //没有查询到客户端要查询的单词
    {
        strcpy(msg.data, "The word not found!");
    }
    else //查到了单词
    {
        strcpy(msg.data, resultp[3]); //将单词意思拷贝到消息体中
                                      //resultp[0]、resultp[1]是表头“word”、“means”
                                      //resultp[2]、resultp[3]是查询到的单词和意思
        /* 将查询记录放入数据库存储(查询成功的单词) */
        time_t t1;
        struct tm *t;
        t1 = time(&t1);
        t = localtime(&t1); //获取时间
        sprintf(date, "%d-%d-%d %d:%d:%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
        sprintf(sql, "insert into history values(\"%s\",\"%s\",\"%s\");", msg.name, resultp[2], date);
        if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0) //插入记录
        {
            fprintf(stderr, "insert history err:%s\n", errmsg);
        }
    }
    if (send(acceptfd, &msg, sizeof(msg), 0) < 0) //消息发送 查询结果
    {
        perror("send err");
        return;
    }
    return;
}
//历史记录
void do_history(int acceptfd, MSG_t msg, sqlite3 *db)
{
    char **resultp = NULL;
    int nrow, ncolumn;
    char *errmsg;
    char sql[128];
    int k = 2;

    sprintf(sql, "select time,word from history where name='%s';", msg.name);
    if (sqlite3_get_table(db, sql, &resultp, &nrow, &ncolumn, &errmsg) != 0)
    {
        fprintf(stderr, "select err:%s\n", errmsg);
        return;
    }
    printf("%d %d\n", nrow, ncolumn);
    printf("%s\n", resultp[0]);
    if (nrow == 0) //没有查询到历史记录
    {
        strcpy(msg.data, "#"); //标志位
        send(acceptfd, &msg, sizeof(msg), 0);
    }
    else //查询到了历史记录
    {
        for (int i = 0; i < nrow; i++)
        {
            sprintf(msg.data, "%s : %s", resultp[k++], resultp[k++]);
            send(acceptfd, &msg, sizeof(msg), 0);
        }
        strcpy(msg.data, "*"); //历史记录发送完成的标志位
        send(acceptfd, &msg, sizeof(msg), 0);
    }
    return;
}