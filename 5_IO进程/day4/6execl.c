/* execl函数簇 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //在一个进程里运行其他的进程
    //1.system
    // system("ls -l");
    // /*execl*/
    // 终端运行ls -l命令，最后以NULL结尾
    execl("/bin/ls","ls",NULL);
    // 运行hello进程
    // 第一个.hello是在当前路径下寻找hello文件
    //第二个.hello是在命令行运行合理的进程
    execl(".hello","./hello",NULL)

    return 0;
}
