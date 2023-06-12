#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

struct msgbuf
{
    long mtype; //消息类型
    char name[32];
    int age;
    float score;
};

int main(int argc, char const *argv[])
{
    //1.创建key
    key_t key = ftok(".", 'c');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("key:%d\n", key);
    //2.创建或打开消息队列
    int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    if (msgid <= 0)
    {
        if (errno == EEXIST)
            msgid = msgget(key, 0666);
        else
        {
            perror("msgget err");
            return -1;
        }
    }
    printf("msgid:%d\n", msgid);
    //3.添加消息
    struct msgbuf msg; //创建msgbuf结构体变量
    msg.mtype = 2;
    strcpy(msg.name, "lihua");
    msg.age = 18;
    msg.score = 99.9999;
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);

    msg.mtype = 1;
    strcpy(msg.name, "xiaoming");
    msg.age = 3;
    msg.score = 66.66;
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);
    //4.读取消息
    struct msgbuf msg_rcv;
    msgrcv(msgid, &msg_rcv, sizeof(msg_rcv) - sizeof(long), 1, 0);
    printf("%s-%d-%f\n",msg_rcv.name, msg_rcv.age, msg_rcv.score);
    msgrcv(msgid, &msg_rcv, sizeof(msg_rcv) - sizeof(long), 2, 0);
    printf("%s-%d-%f\n",msg_rcv.name, msg_rcv.age, msg_rcv.score);
    msgrcv(msgid, &msg_rcv, sizeof(msg_rcv) - sizeof(long), 3, 0);
    printf("%s-%d-%f\n",msg_rcv.name, msg_rcv.age, msg_rcv.score);
    //5.删除消息队列
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
