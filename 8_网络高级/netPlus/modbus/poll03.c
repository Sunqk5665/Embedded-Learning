#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int sockfd;

void set_slave_id(uint8_t *p, int id) //设置从机id
{
    p[6] = id;
}
void read_register(uint8_t *p, int addr, int nb, uint8_t *dest)
{
    //1.写协议
    p[5] = 0x06; //长度

    p[7] = 0x03; //功能
    p[8] = addr >> 8;
    p[9] = addr & 0xff; //起始地址
    p[10] = nb >> 8;
    p[11] = nb & 0xff; //数量

    send(sockfd, p, 12, 0);
    recv(sockfd, dest, 32, 0);
}
//写单个线圈
void write_coil(uint8_t *p, int addr, int flag, uint8_t *dest)
{//write_coil(存协议的数组首地址, 起始地址, 断通标志, )
    p[5] = 0x06;

    p[7] = 0x05;
    p[8] = addr >> 8;
    p[9] = addr & 0xff; //起始地址
    p[10] = (flag == 1 ? 0xff : 0x00); //断通标志
    p[11] = flag & 0x00;

    send(sockfd, p, 12, 0);
    recv(sockfd, dest, 32, 0);
}

int main(int argc, char const *argv[])
{ //1.socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    printf("sockfd=%d\n", sockfd);
    // 填充IPV4通信结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(502);
    saddr.sin_addr.s_addr = inet_addr("192.168.50.202");
    // connect
    int connectval = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (connectval < 0)
    {
        perror("connect err.");
        return -1;
    }
    printf("connect ok...\n");

    uint8_t buf[12] = {0};
    uint8_t dest[12] = {0};

    set_slave_id(buf, 1); //从机id(协议第七位)
    // read_register(buf, 0, 2, dest);
    write_coil(buf, 0, 1, dest); //

    close(sockfd);
    return 0;
}
