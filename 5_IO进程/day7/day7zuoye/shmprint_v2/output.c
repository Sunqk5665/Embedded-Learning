#include "shm.h"

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
        //若以创建，给shmid重新赋值
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
    //读操作
    while(1)
    {
        if(stp->flag == 1)
        {
            fputs(stp->buf,stdout);
            stp->flag = 0;
            if(strcmp(stp->buf,"quit\n")==0)
            {
                break;
            }
            // memset(stp->buf,0,32);//清空共享内存
        }
    }
    return 0;
}
