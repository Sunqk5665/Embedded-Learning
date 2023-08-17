/*
    两个进程实现通信，一个进程循环从终端输入，另一个进程循环打印，当输入quit时结束。共享内存实现。
    文件IO
*/
#include "head.h"

int main(int argc, char const *argv[])
{
    //1.key
    key_t key = ftok("./input.c", 'a');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    //2.创建或打开共享内存
    int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid < 0)
    {
        if (errno == EEXIST)
        {
            shmid = shmget(key, 128, 0666);
        }
        else
        {
            perror("shmget err");
            return -1;
        }
    }
    printf("shmid:%d\n", shmid);
    //3.映射
    struct shm *p = (struct shm *)shmat(shmid, NULL, 0);
    p->flag = 0;
    if (p == (struct shm *)-1)
    {
        perror("shmat err");
        return -1;
    }

    p->s = 0;
    while (1)
    {
        if (p->flag == 0)
        {
            p->s = read(0, p->buf, 128);
            p->flag = 1;
            if(strncmp(p->buf,"quit\n",5)==0)
                break;
        }
    }
    //4.取消映射
    shmdt(p);
    //5.删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
