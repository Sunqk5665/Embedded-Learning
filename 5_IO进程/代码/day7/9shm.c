#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    key_t key = 1;
    int shmid = shmget(key,256,IPC_CREAT|IPC_EXCL|0666);
    if(shmid < 0)
    {
        if(errno == 17)
        {
            shmid = shmget(key,256,0666);;
        }
        else
        {
            perror("shmget err");
            return -1;
        }
    }
    printf("shmid=%d\n",shmid);

    return 0;
}
