/*
    任务：编程实现采集传感器数据和控制硬件设备（传感器和硬件通过slave模拟）
	    传感器：2个，光线传感器、加速度传感器（x\y\z）
	    硬件设备：2个，led灯、蜂鸣器
    要求：
	1）多任务编程：多线程
	2）循环1s采集一次数据，并将数据打印至终端
	3）同时从终端输入指令控制硬件设备	
	    0 1：led灯打开
        0 0：led灯关闭
        1 1：蜂鸣器开
        1 0: 蜂鸣器关
*/
#include <stdio.h>
#include <modbus.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

modbus_t *p;

void *handler(void *arg)
{
    uint16_t dest[4];
    while (1)
    {
        if (modbus_read_registers(p, 0, 4, dest) < 0)
        {
            printf("modbus_read_registers err\n");
            return NULL;
        }
        printf("光线传感器:%d X:%d Y:%d Z:%d\n", dest[0], dest[1], dest[2], dest[3]);
        sleep(4);
    }
    // 5.关闭套接字
    // modbus_close(p);
}
int main(int argc, char const *argv[])
{
    // 1.创建实例
    p = modbus_new_tcp("192.168.8.200", 502);
    if (p == NULL)
    {
        printf("modbus_new_tcp err\n");
        return -1;
    }
    // 2.设置从机ID
    modbus_set_slave(p, 1);
    // 3.和从机进行连接
    if (modbus_connect(p))
    {
        printf("modbus_connect err\n");
        return -1;
    }

    pthread_t tid;
    if (pthread_create(&tid, NULL, handler, NULL) != 0) //创建线程
    {
        perror("pthread_create err");
        return -1;
    }

    // 4.寄存器操作（调用功能码对应函数）
    // int r ;
    // int l ;
    char str[4];
    while (1)
    {
        // scanf("%d %d", &r, &l);
        fgets(str,4,stdin);
        if (strncmp(str,"0 1",3)==0)    //0 1：led灯打开
            modbus_write_bit(p, 0, 1);
        if (strncmp(str,"0 0",3)==0) //0 0：led灯关闭
            modbus_write_bit(p, 0, 0);
        if (strncmp(str,"1 1",3)==0) //1 1：蜂鸣器开
            modbus_write_bit(p, 1, 1);
        if (strncmp(str,"1 0",3)==0) //1 0: 蜂鸣器关
            modbus_write_bit(p, 1, 0);
    }

    // 5.关闭套接字
    modbus_close(p);
    // 6.释放实例
    modbus_free(p);
    return 0;
}
