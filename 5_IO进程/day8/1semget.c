#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

union semun
{
    int val;
};
int main(int argc, char const *argv[])
{
    //创建key值
    key_t key = ftok(".",'a');
    if(key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("key:%d\n",key);
    //2.创建或打开信号灯集
    int semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666);
    if(semid <= 0)
    {
        if(errno == EEXIST)
            semid = semget(key,2,0666);
        else
        {
            perror("semget err");
            return -1;
        }
    }
    else
    {
        //3.初始化
        union semun sem;

        sem.val = 0;
        semctl(semid, 0, SETVAL, sem);

        sem.val = 5;
        semctl(semid, 1, SETVAL, sem);
    }
    printf("semid:%d\n",semid);

    //4.pv操作
    struct sembuf buf;
    //v
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    semop(semid, &buf, 1);
    //p
    buf.sem_num = 1;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    semop(semid, &buf, 1);

    printf("0:%d\n",semctl(semid, 0, GETVAL));
    printf("1:%d\n",semctl(semid, 1, GETVAL));
    //5.删除信号灯集
    semctl(semid,0,IPC_RMID);
    return 0;
}
