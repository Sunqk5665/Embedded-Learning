#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("start...\n");
    // alarm(5);
    
    printf("%d\n",alarm(5));
    printf("end...\n");
    
    sleep(3);
    printf("%d\n",alarm(8));
    printf("second end...\n");
    // alarm(8);
    pause();

    return 0;
}

