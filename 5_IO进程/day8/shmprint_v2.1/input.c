#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/sem.h>
#include <string.h>


union semun //创建共用体
{
    int val;
};
int main(int argc, char const *argv[])
{
    //创建key值
    int key = ftok(".", 'd');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    //创建或打开共享内存
    int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
    if(shmid <= 0)
    {
        if(errno == EEXIST)
            shmid = shmget(key,128,0666);
        else
        {
            perror("shmget err");
            return -1;
        }
    }
    //创建或打开信号灯集
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
    { 
        union semun sem; //共用体变量

        sem.val = 0;
        semctl(semid, 0, SETVAL, sem);
    }
    //映射
    char *p = (char *)shmat(shmid,NULL,0);
    if(p == (char *)-1)
    {
        perror("shmat err");
        return -1;
    }
    struct sembuf stbuf;
    while (1)
    {
        fgets(p,32,stdin);
        //v
        stbuf.sem_num = 0;
        stbuf.sem_op = 1;
        stbuf.sem_flg = 0;
        semop(semid,&stbuf,1);

        if (strcmp(p, "quit\n") == 0)
        {
            break;
        }
    }
    //撤销映射
    shmdt(p);
    //删除共享内存
    shmctl(shmid,IPC_RMID,NULL);
    //删除信号灯集
    semctl(semid, 0, IPC_RMID);

    return 0;
}
