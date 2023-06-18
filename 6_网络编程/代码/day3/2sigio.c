#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int fd_mouse;
void handler(int sig)
{
    char buf[32];
    int ret = read(fd_mouse, buf, sizeof(buf) - 1);
    buf[ret] = '\0';
    printf("buf=%s", buf);
}

int main(int argc, char const *argv[])
{
    fd_mouse = open("/dev/input/mouse0", O_RDONLY);//打开鼠标文件
    if (fd_mouse < 0)
    {
        perror("open mouse err.");
        return -1;
    }
    //1.将文件描述符和进程ID告诉给底层驱动
    fcntl(fd_mouse, F_SETOWN, getpid());
    //2.设置文件描述符异步通知特性
    int flags = fcntl(fd_mouse, F_GETFL);
    flags |= O_ASYNC;    //将异步特性添加到flags中
    fcntl(fd_mouse, F_SETFL, flags);//将上面特性设置上
    //3.注册signal信号
    signal(SIGIO, handler);

    while (1)
    {
        sleep(1);
        printf("hello world\n");
    }
    close(fd_mouse);
    return 0;
}
