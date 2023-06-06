#include <unistd.h>
#include <stdio.h>
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
        while(1);
    }
    else{
        a=3;
        printf("parent a:%d\n",a);
        //while(1);
    }
    return 0;
}
