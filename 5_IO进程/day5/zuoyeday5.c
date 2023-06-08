#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    char buf[32] = {0};
    int fd[2] = {0};
    if(pipe(fd)<0) //创建无名管道
    {
        perror("pipe err");
        return -1;
    }

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork err");
        return -1;
    }
    else if(pid == 0)
    {
        while (1)//子进程循环从管道读取数据，为空阻塞
        {
            read(fd[0],buf,32);
            if(strcmp(buf,"quit")==0)
                //return 0;
                exit(0);
            printf("%s\n",buf);

        }
        
    }
    else
    {
        while(1)//父进程循环往管道写入数据
        {
            //scanf("%s",buf);
            fgets(buf,32,stdin);
            if(buf[strlen(buf)-1] == '\n')
                buf[strlen(buf)-1] = '\0';
            write(fd[1],buf,strlen(buf)+1);
            if(strcmp(buf,"quit")==0)
                //return 0;
                exit(0);
        }
        waitpid(pid,NULL,0);
    }
    close(fd[0]);
    close(fd[1]);
    
    return 0;
}
