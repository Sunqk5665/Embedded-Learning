/*
    两个进程实现通信，一个进程循环从终端输入，另一个进程循环打印，当输入quit时结束。共享内存实现。
    建议大家先用标志位的方式实现，不建议使用信号量。
    标准IO，fgets fputs
*/
#include "shm.h"

int main(int argc, char const *argv[])
{   
    //创建key值
    key_t key; 
    key = ftok("./key.txt",'1');
    if(key<0)
    {
        perror("ftok err");
        return -1;
    }

    //创建或打开共享内存
    int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
    if(shmid <= 0) //=0不使用
    {
        //若已经创建，给shmid重新赋值
        if(errno == 17)
            shmid = shmget(key, 128, 0666);
        else
        {
            perror("shmget err");
            return -1;
        }
    }
    //映射
    struct ff *stp = shmat(shmid,NULL,0);
    stp->flag = 0;
    if(stp==(void *)-1)
    {
        perror("shmat err");
        return -1;
    }

    //写操作
    while(1)
    {
        if(stp->flag == 0)//判断标志位
        {
            fgets(stp->buf,32,stdin);//将终端输入放到共享内存
            stp->flag = 1;
            if(strcmp(stp->buf,"quit\n")==0)
            {
                break;
            }
        }
    }
    return 0;
}
