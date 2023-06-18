#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    //更改文件描述符0的属性
    //1.获取文件描述符原有的属性信息
    int flags = fcntl(0, F_GETFL);
    //2.修改添加权限
    flags |= O_NONBLOCK;
    //3.将修改好的权限设置回去
    fcntl(0, F_SETFL, flags);

    char buf[32] = {0};
    while (1)
    {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
        {
            perror("fgets err.");
        }
        printf("buf:%s\n", buf);
        sleep(1);
    }
    return 0;
}
