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
    char *p = shmat(shmid,NULL,0);
    if(p==(void *)-1)
    {
        perror("shmat err");
        return -1;
    }
    //读操作
    while(1)
    {   //共享内存存放的字符串最后一位为标志位，判断是否可读
        if(p[strlen(p)-1]=='1')
        {//将共享内存中的字符串输出，不输出最后一位的标志位
            write(1,p,strlen(p)-1);
            putchar(10);
            if(strcmp(p,"quit1")==0)
                break;
            memset(p,0,32);//清空共享内存
            p[0]='0';
            p[1]='\0';//设置写的标志位'0'
        }
    }
    return 0;
}
