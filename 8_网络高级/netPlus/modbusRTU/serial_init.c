#include <termios.h>

void uart_init(int fd) //串口初始化
{
    struct termios options;
    //设置串口属性
	//获取串口原有属性
    tcgetattr(fd, &options);
	//激活选项CLOCAL(本地连接)和CREAD(接受使能)
    options.c_cflag |= ( CLOCAL | CREAD );
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