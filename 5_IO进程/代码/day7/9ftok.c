/*
    共享内存创建及读写
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /*1.创建key值*/
    key_t key;
    key = ftok("./6kill.c", 'a'); //第二个参数是任意字符
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("%#x\n", key); //'#'会在打印结果中添加前缀0x

    /*2.创建或打开共享内存*/
    int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid <= 0) //=0不使用
    {
        //若已创建，则用shmget打开，重新给shmid赋值
        if (errno == 17)
            shmid = shmget(key, 128, 0666);
        else
        {
            perror("shmget err");
            return -1;
        }
    }
    printf("shmid:%d\n", shmid);
    /*3.映射共享内存到用户空间 */
    char *p = (char *)shmat(shmid, NULL, 0);
    if (p == (char *)-1)
    {
        perror("shmat err");
        return -1;
    }
    //读写操作
    read(0, p, 32);
    write(1, p, 32);
    //printf("buf:%s\n",p);

    /*4.撤销映射*/
    shmdt(p);
    /*5.删除共享内存*/
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
