#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

union semun {
    int val;
};
void myinit(int semid,int num,int val) //3.信号灯集初始化函数
{
    union semun sem;
    sem.val = val;
    semctl(semid, num, SETVAL, sem);
}
void semop(int semid,int num,int op) //4.pv操作函数
{
    struct sembuf buf;
    buf.sem_num = num;
    buf.sem_op = op;
    buf.sem_flg = 0;
    semop(semid, &buf, 1);
}
int main(int argc, char const *argv[])
{
    //创建key值
    key_t key = ftok(".", 'a');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("key:%d\n", key);
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
        myinit(semid,1,5);
    }
    printf("semid:%d\n", semid);
    //4.pv操作
    semop(semid,0,1);
    semop(semid,1,-1);

    printf("0:%d\n", semctl(semid, 0, GETVAL));
    printf("1:%d\n", semctl(semid, 1, GETVAL));
    //5.删除信号灯集
    semctl(semid, 0, IPC_RMID);
    return 0;
}
