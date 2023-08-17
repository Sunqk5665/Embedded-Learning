#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

union semun //创建共用体
{
    int val;
};
int main(int argc, char const *argv[])
{
#if 1
    //1.创建key值
    key_t key = ftok(".", 'a');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("key:%d\n", key);
    //2.创建或打开信号灯集
    int semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666); //创建信号灯集，包含2个信号灯
    if (semid <= 0)
    {
        if (errno == EEXIST) //存在则只打开
            semid = semget(key, 2, 0666);
        else
        {
            perror("semget err");
            return -1;
        }
    }
#endif
#if 1
    else                 //3.初始化。若信号灯集已经创建好，则不需要初始化
    {                    // 所以要放到else里面
        union semun sem; //共用体变量

        sem.val = 0;
        semctl(semid, 0, SETVAL, sem);

        sem.val = 5;
        semctl(semid, 1, SETVAL, sem);
    }
    printf("semid:%d\n", semid);
    printf("0:%d\n", semctl(semid, 0, GETVAL));
    printf("1:%d\n", semctl(semid, 1, GETVAL));
    //4.pv操作
    struct sembuf buf;
    //v
    buf.sem_num = 0; //信号灯编号
    buf.sem_op = 1;  //sem.val+1
    buf.sem_flg = 0; //阻塞：当信号的值减为0时，申请不到资源，阻塞
    semop(semid, &buf, 1); //1:1个灯
    //p
    buf.sem_num = 1; //信号灯编号
    buf.sem_op = -1; //sem.val-1
    buf.sem_flg = 0; //阻塞：当信号的值减为0时，申请不到资源，阻塞
    semop(semid, &buf, 1);

    printf("0:%d\n", semctl(semid, 0, GETVAL));
    printf("1:%d\n", semctl(semid, 1, GETVAL));
    //5.删除信号灯集
    semctl(semid, 0, IPC_RMID); //只删除一个信号灯，所有信号灯都将被删除
#endif
    return 0;
}
