#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
    int fd_mouse = open("/dev/input/mouse0", O_RDONLY);
    if (fd_mouse < 0)
    {
        perror("open mouse err.");
        return -1;
    }
    //引入->IO多路复用
    //1.创建一个表
    fd_set readfds, tempfds;
    FD_ZERO(&readfds); //清空表
    //2.将关心的文件描述符添加到表中
    FD_SET(0, &readfds);
    FD_SET(fd_mouse, &readfds);
    int maxfd = fd_mouse;
    char buf[32];
    while (1)
    {
        tempfds = readfds;
        //3.调用函数监听
        int ret = select(maxfd+1, &tempfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select err.");
            return -1;
        }
        //4.有一个或多个IO准备好就返回
        //5.判断哪个文件描述符产生事件
        if (FD_ISSET(0, &tempfds))
        {
            //6处理事件
            //键盘
            fgets(buf, sizeof(buf), stdin);
            printf("key:%s\n", buf);
        }
        if (FD_ISSET(fd_mouse, &tempfds))
        {
            //鼠标
            int ret = read(fd_mouse, buf, sizeof(buf) - 1);
            buf[ret] = '\0';
            printf("mouse:%s\n", buf);
        }
    }
    close(fd_mouse);
    return 0;
}
