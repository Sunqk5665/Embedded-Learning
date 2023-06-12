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
#include <sys/sem.h>

union semun {
    int val;
};
void myinit(int semid,int num,int val)
{
    //3.初始化
    union semun sem;

    sem.val = val;
    semctl(semid, num, SETVAL, sem);
}
void sem_op(int semid,int num,int op)
{//4.pv操作
    struct sembuf buf;
    buf.sem_num = num;
    buf.sem_op = op;
    buf.sem_flg = 0;
    semop(semid, &buf, 1);
}
int main(int argc, char const *argv[])
{
    //创建key值
    key_t key;
    key = ftok(".", 'a');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }

    //创建或打开共享内存
    int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid <= 0) //=0不使用
    {
        //若已经创建，给shmid重新赋值
        if (errno == 17)
            shmid = shmget(key, 128, 0666);
        else
        {
            perror("shmget err");
            return -1;
        }
    }
    //映射
    char *p = shmat(shmid, NULL, 0);
    if (p == (void *)-1)
    {
        perror("shmat err");
        return -1;
    }

    //2.创建或打开信号灯集
    int semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666);
    if (semid <= 0)
    {
        if (errno == EEXIST)
            semid = semget(key, 2, 0666);
        else
        {
            perror("semget err");
            return -1;
        }
    }
    else
    {//3.初始化
        myinit(semid,0,0);
    }
    printf("semid:%d\n", semid);  

    //写操作
    while (1)
    {
        fgets(p, 32, stdin); //将终端输入放到共享内存
        sem_op(semid,0,1); //v
        printf("0:%d\n", semctl(semid, 0, GETVAL));
        if (strcmp(p, "quit\n") == 0)
        {
            break;
        }
    }
    //5.删除信号灯集
    semctl(semid, 0, IPC_RMID);
    return 0;
}
