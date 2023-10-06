//03功能
#include <stdio.h>
#include <modbus.h>

int main(int argc, char const *argv[])
{
    // 1.创建实例
    modbus_t *p = modbus_new_tcp("192.168.50.202", 502);
    if(p == NULL)
    {
        printf("modbus_new_tcp err\n");
        return -1;
    }
    // 2.设置从机ID
    modbus_set_slave(p,1);
    // 3.和从机进行连接
    if(modbus_connect(p))
    {
        printf("modbus_connect err\n");
        return -1;
    }
    // 4.寄存器操作（调用功能码对应函数）
    uint16_t dest[32];
    if(modbus_read_registers(p,0,2,dest)<0)
    {
        printf("modbus_read_registers err\n");
        return -1;
    }
    for (int i = 0; i < 2; i++)
    {
        printf("%02x ",dest[i]);
    }
    printf("\n");
    
    // 5.关闭套接字
    modbus_close(p);
    // 6.释放实例
    modbus_free(p);

    return 0;
}
