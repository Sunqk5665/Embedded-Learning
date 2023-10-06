#include <stdio.h>
#include <unistd.h>
// 若父进程先结束，子进程将变成孤儿进程 且被init进程收养，变成孤儿进程
// 若子进程先结束，父进程如果没与及时回收，子进程将变成僵尸进程
int main(int argc, char const *argv[])
{
    int a =0;
    pid_t pid = fork();
    if(pid<0){
        perror("fork err");
        return -1;
    }
    else if(pid == 0){ // 运行子进程
        printf("child a:%d\n",a);
        while(1);
    }
    else{  // 运行父进程
        a=3;
        printf("parent a:%d\n",a);
        //while(1);
    }
    return 0;
}
