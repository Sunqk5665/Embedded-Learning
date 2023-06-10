#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //1.创建key值
    key_t key;
    key = ftok("./6kill.c",'1');//第二个参数是任意字符
    if(key<0)
    {
        perror("ftok err");
        return -1;
    }
    printf("%#x\n",key);//'#'会在打印结果中添加前缀0x

    //2.创建或打开共享内存
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
    printf("shmid:%d\n",shmid);
    //映射
    char *p = shmat(shmid,NULL,0);
    if(p==(void *)-1)
    {
        perror("shmat err");
        return -1;
    }
    //读写操作
    read(0,p,32);
    write(1,p,32);
    //printf("buf:%s\n",p);

    return 0;
}
