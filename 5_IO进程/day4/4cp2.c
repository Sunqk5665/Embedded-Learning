#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
//通过父子进程完成对文件的拷贝(cp)，父进程从文件开始到文件
//的一半开始拷贝，子进程从文件的一半到文件末尾。要求：文件IO cp src dest
int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        printf("Please input:%s <srcfile> <destfile>\n",argv[0]);
        return -1;
    }

    char buf[32] = {0};
    int src = open(argv[1],O_RDWR);
    if(src<0)
    {
        perror("src open err");
        return -1;
    }
    int dest = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0666);
    if(src<0)
    {
        perror("src open err");
        return -1;
    }
    ssize_t s;
    __off_t len = lseek(src,0,SEEK_END)/2; //获取文件一半的长度
    int flag = 0;
    
    pid_t pid = fork(); //创建子进程
    if(pid<0){
        perror("fork err");
        return -1;
    }
    else if(pid == 0)  //子进程
    {
        while(flag == 1)
        {
            lseek(src,len,SEEK_SET);
            lseek(dest,len,SEEK_SET);
            while((s=read(src,buf,32))!=0)
                write(dest,buf,s);
            flag = 0;
            break;
        }
    }
    else   //父进程
    {
        lseek(src,0,SEEK_SET);
        lseek(dest,0,SEEK_SET);
        while(len>0)
        {
            if(len > 32)
                s = read(src,buf,32);
            else
                s = read(src,buf,len);
            write(dest,buf,s);
            len -= s;
        }
        flag = 1;
        wait(NULL);
    }
    close(src);
    close(dest);
    return 0;
}
