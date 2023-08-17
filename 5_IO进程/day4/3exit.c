#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void fun(int a, int b)
{
    printf("a+b=%d",a+b);
    exit(0); // 结束进程，刷新缓存
    // _exit(0); // 结束进程，不刷新缓存
    return;
}

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if(pid<0){
        perror("fork err");
        return -1;
    }
    else if(pid == 0){
        printf("in child\n");
        fun(3,4);
        sleep(1);
    }
    else{
        printf("in parent\n");
        // while(1);
        wait(NULL);
        printf("parent end...\n");
    }
    return 0;
}
