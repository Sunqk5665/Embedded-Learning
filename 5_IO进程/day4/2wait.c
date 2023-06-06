#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    int a =0;
    pid_t pid = fork();
    if(pid<0){
        perror("fork err");
        return -1;
    }
    else if(pid == 0){
        printf("child a:%d\n",a);
        //while(1);
    }
    else{
        a=3;
        wait(NULL);//阻塞回收所有子进程
        //waitpid(-1,NULL,0);//阻塞回收所有子进程
        //waitpid(pid,NULL,WNOHANG); //不阻塞回收进策划那个号为pid的进程
        printf("parent a:%d\n",a);
        //while(1);
    }
    return 0;
}
