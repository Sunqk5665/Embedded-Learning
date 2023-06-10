/*
两个进程实现通信，一个进程循环从终端输入，另一个进程循环打印，当输入quit时结束。共享内存实现。
建议大家先用标志位的方式实现，不建议使用信号量。
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
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
    char *p = shmat(shmid,NULL,0);
    if(p==(void *)-1)
    {
        perror("shmat err");
        return -1;
    }

    p[0]='0';//共享内存空间初始标志为'0'
    p[1]='\0';
    //写操作
    ssize_t s;
    while(1)
    {
        if(p[strlen(p)-1]=='0')//判断标志位
        {
            s = read(0,p,32);//将终端输入放到共享内存
            p[s-1] = '1';//设置读入字符串最后一位为'1'(覆盖了'\n')，表示可以读
            p[s] = '\0';//将所输入字符串最后('1'后面)添加'\0'，表示字符串结尾
            if(strcmp(p,"quit1")==0)
            {
                break;
            }
        }
    }
    return 0;
}
