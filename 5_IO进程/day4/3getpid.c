#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if(pid<0)
    {
        perror("fork err");
        return -1;
    }
    else if(pid == 0)
    {
        printf("childpid:%d ppid:%d pid:%d\n",getpid(),getppid(),pid);
        exit(0);
    }
    else
    {
        printf("parentpid:%d ppid:%d pid:%d\n",getpid(),getppid(),pid);
        wait(NULL);
    }
    return 0;
}
