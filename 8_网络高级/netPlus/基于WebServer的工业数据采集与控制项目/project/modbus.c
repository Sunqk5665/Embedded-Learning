/*
    连接服务器和slave端，
*/
#include <stdio.h>
#include <modbus.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/msg.h>

void *handler(void *arg);

modbus_t *mod;
key_t key;

struct msgbuf
{
    long mtype;      //消息类型，要为long型且放到第一个
    char setstr[32]; //下面的自己定义
};

int main(int argc, char const *argv[])
{
    // 1.创建实例
    mod = modbus_new_tcp("192.168.0.107", 502);
    if (mod == NULL)
    {
        printf("modbus_new_tcp err\n");
        return -1;
    }
    // 2.设置从机ID
    modbus_set_slave(mod, 1);
    // 3.和从机进行连接
    if (modbus_connect(mod))
    {
        printf("modbus_connect err\n");
        return -1;
    }

    //(1)创建key值
    key = ftok("./", 'a');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("%#x\n", key);

    pthread_t tid;
    if (pthread_create(&tid, NULL, handler, NULL) != 0) //创建线程
    {
        perror("pthread_create err");
        return -1;
    }
    /******************/
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
    struct msgbuf msg; //创建msgbuf结构体变量
    
    // 寄存器操作（调用功能码对应函数）
    int led, beep;
    while (1)
    {
        msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0);
        printf("modbus.c:%s\n",msg.setstr);
        //获取值
        // sscanf(msg.setstr, "\"led=%dbeep=%d\"", &led, &beep);
        // printf("led:%d beep:%d\n",led,beep);
        if(strncmp(msg.setstr,"\"led",4)==0)
        {
            sscanf(msg.setstr,"\"led=%d\"",&led);//获取值
            modbus_write_bit(mod, 0, led);
        }
        if(strncmp(msg.setstr,"\"beep",5)==0)
        {
            sscanf(msg.setstr,"\"beep=%d\"",&beep);
            modbus_write_bit(mod, 1, beep);
        }
    }

    // 5.关闭套接字
    modbus_close(mod);
    // 6.释放实例
    modbus_free(mod);
    return 0;
}

void *handler(void *arg) //线程处理函数，负责采集数据
{
    uint16_t *p;
    //(2)创建或打开共享内存
    int shmid = shmget(key, 8, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid <= 0)
    {
        if (errno == 17) //若已创建，则用shmget打开，重新给shmid赋值
            shmid = shmget(key, 8, 0666);
        else
        {
            perror("shmget err.");
            return NULL;
        }
    }
    printf("shmid:%d\n", shmid);
    //(3)映射共享内存到用户空间
    p = shmat(shmid, NULL, 0);
    if (p == (void *)-1)
    {
        perror("shmat err.");
        return NULL;
    }
    while (1)
    {
        if (modbus_read_registers(mod, 0, 4, p) < 0) //直接放到共享内存
        {
            printf("modbus_read_registers err\n");
            return NULL;
        }
        printf("光线传感器:%d X:%d Y:%d Z:%d\n", p[0], p[1], p[2], p[3]); //打印共享内存信息
        sleep(4);
    }
    //(4)撤销映射
    shmdt(p);
    //(5)删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
}
