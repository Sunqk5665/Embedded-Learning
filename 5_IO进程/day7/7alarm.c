#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("start...\n");
    // alarm(5); //alarm不阻塞，当时间到达后结束进程
    
    printf("%d\n",alarm(5));//第一次调用alarm返回值为0
                            //alarm不阻塞，当时间到达后结束进程
    printf("end...\n");
    
    sleep(3);
    printf("%d\n",alarm(8)); // 前面定时5秒。用sleep函数消耗1秒，alarm返回5-3=2
    printf("second end...\n");
    alarm(0); //当秒数为0时，定时被取消
    
    pause(); //pause挂起进程（用while也可以），直到捕捉到信号才会返回

    return 0;
}

