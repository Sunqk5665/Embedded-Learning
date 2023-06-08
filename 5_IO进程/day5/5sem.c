#include <stdio.h>
#include <semaphore.h>

int main(int argc, char const *argv[])
{
    sem_t sem;
    if(sem_init(&sem,1,2)<0)
    {
        perror("sem_init err\n");
        return -1;
    }
    printf("sem_init success\n");
    sem_wait(&sem);
    printf("first\n");
    sem_wait(&sem);
    printf("second\n");
    sem_wait(&sem);
    printf("third\n");
    
    return 0;
}
