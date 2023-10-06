#include <stdio.h>
#include <termios.h>
#include "Crc_Calc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void uart_init(int fd) //串口初始化
{
    struct termios options;
    //设置串口属性
    //获取串口原有属性
    tcgetattr(fd, &options);
    //激活选项CLOCAL(本地连接)和CREAD(接受使能)
    options.c_cflag |= (CLOCAL | CREAD);
    //设置字符大小
    options.c_cflag &= ~CSIZE;
    //设置流控
    options.c_cflag &= ~CRTSCTS;
    //设置8位数据位
    options.c_cflag |= CS8;
    //设置停止位
    options.c_cflag &= ~CSTOPB;
    //忽略奇偶错字符
    options.c_iflag |= IGNPAR;
    //将输入的CR转换为NL和停止输出控制流起作用
    options.c_iflag &= ~(ICRNL | IXON);
    options.c_oflag = 0;
    options.c_lflag = 0;
    //设置波特率(输入和输出的波特率)
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    //激活配置
    tcsetattr(fd, TCSANOW, &options);
}

int main(int argc, char const *argv[])
{
    int fd = open("/dev/ttyS1", O_RDWR);
    if (fd < 0)
    {
        perror("open err");
        return -1;
    }
    //串口初始化
    uart_init(fd);
    //写协议，生成校验码
    unsigned char buf[8] = {0};
    unsigned char recvbuf[32] = {0};
    unsigned short crc;
    buf[0] = 0x01;
    buf[1] = 0x03;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x00;
    buf[5] = 0x01;
    crc = GetCRC16(buf, 6);
    buf[6] = crc >> 8;
    buf[7] = crc;

    //写
    write(fd, buf, 8);
    //读
    read(fd, recvbuf, sizeof(recvbuf));
    //打印
    for (int i = 0; i < 7; i++)
    {
        printf("%02x ", recvbuf[i]);
    }
    printf("\n");
    //关闭文件
    close(fd);
    return 0;
}
