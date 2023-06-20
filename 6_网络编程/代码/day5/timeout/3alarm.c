#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    printf("time out............\n");
}
int main(int argc, char const *argv[])
{
    struct sigaction act;
    //
    sigaction(SIGALARM,NULL,&act);
    // 修改
    act.sa_handler = handler;
    sigaction(SIGALRM,&act,NULL);
    
    char buf[32];
    while(1)
    {
        alarm(2);
        if(fgets(buf,sizeof(buf),stdin)==NULL)
        {
            perror("fgets err.");
        }
        printf("buf:%s\n",buf)
    }
    return 0;
}
