/***********************************************************************************
Copy right:	    hqyj Tech.
Author:         jiaoyue
Date:           2023.07.01
Description:    http请求处理
***********************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include "custom_handle.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>



#define KB 1024
#define HTML_SIZE (64 * KB)

//普通的文本回复需要增加html头部
#define HTML_HEAD "Content-Type: text/html\r\n" \
				  "Connection: close\r\n"

static int handle_login(int sock, const char *input)
{
    char reply_buf[HTML_SIZE] = {0};
    char *uname = strstr(input, "username=");
    uname += strlen("username=");
    char *p = strstr(input, "password");
    *(p - 1) = '\0';
    printf("username = %s\n", uname);

    char *passwd = p + strlen("password=");
    printf("passwd = %s\n", passwd);

    if(strcmp(uname, "admin")==0 && strcmp(passwd, "admin")==0)
    {
        sprintf(reply_buf, "<script>localStorage.setItem('usr_user_name', '%s');</script>", uname);
        strcat(reply_buf, "<script>window.location.href = '/index.html';</script>");
        send(sock,reply_buf,strlen(reply_buf),0);
    }
    else
    {
        printf("web login failed\n");

        //"用户名或密码错误"提示，chrome浏览器直接输送utf-8字符流乱码，没有找到太好解决方案，先过渡
        char out[128] = {0xd3,0xc3,0xbb,0xa7,0xc3,0xfb,0xbb,0xf2,0xc3,0xdc,0xc2,0xeb,0xb4,0xed,0xce,0xf3};
        sprintf(reply_buf, "<script charset='gb2312'>alert('%s');</script>", out);
        strcat(reply_buf, "<script>window.location.href = '/login.html';</script>");
        send(sock,reply_buf,strlen(reply_buf),0);
    }

    return 0;
}

static int handle_add(int sock, const char *input)
{
    int number1, number2;
    
    //input必须是"data1=1data2=6"类似的格式，注意前端过来的字符串会有双引号
    sscanf(input, "\"data1=%ddata2=%d\"", &number1, &number2);
    printf("num1 = %d\n", number1);

    char reply_buf[HTML_SIZE] = {0};
    printf("num = %d\n", number1*number2);
    sprintf(reply_buf, "%d", number1*number2);
    printf("resp = %s\n", reply_buf);
    send(sock,reply_buf,strlen(reply_buf),0);

    return 0;
}

//从共享内存取数据
int handler_get(int sock, const char *input)
{
    uint16_t *p = NULL;
    /****创建共享内存****/
    //(1)创建key值
    key_t key = ftok("./", 'a');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("%#x\n", key);
    //(2)创建或打开共享内存
    int shmid = shmget(key, 8, IPC_CREAT | IPC_EXCL | 0666);
    if(shmid <= 0)
    {
        if(errno == 17)//若已创建，则用shmget打开，重新给shmid赋值
            shmid = shmget(key, 8, 0666);
        else
        {
            perror("shmget err.");
            return -1;
        }
    }
    printf("shmid:%d\n",shmid);
    //(3)映射共享内存到用户空间
    p = shmat(shmid,NULL,0);
    if(p == (void *)-1)
    {
        perror("shmat err.");
        return -1;
    }
    printf("光线传感器:%d X:%d Y:%d Z:%d\n", p[0], p[1], p[2], p[3]); //打印共享内存信息

    char reply_buf[HTML_SIZE] = {0};
    sprintf(reply_buf, "光线:%d X:%d Y:%d Z:%d", p[0], p[1], p[2], p[3]);
    printf("reply_buf = %s\n", reply_buf);
    send(sock,reply_buf,strlen(reply_buf),0);
    /******************/
    return 0;
}

struct msgbuf
{
    long mtype; //消息类型，要为long型且放到第一个
    char setstr[32]; //下面的自己定义
};
int handler_set(int sock, const char *input)
{
    // int led,beep;
    // sscanf(input, "\"led=%dbeep=%d\"", &led, &beep);
    //1.创建key
    key_t key = ftok("./", 'a');
    if (key < 0)
    {
        perror("ftok err");
        return -1;
    }
    printf("key:%d\n", key);
    //2.创建或打开消息队列
    int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    if (msgid <= 0)
    {
        if (errno == EEXIST)
            msgid = msgget(key, 0666);
        else
        {
            perror("msgget err");
            return -1;
        }
    }
    printf("msgid:%d\n", msgid);
    struct msgbuf msg; //创建msgbuf结构体变量
    msg.mtype = 1;
    strcpy(msg.setstr,input);
    printf("handler_set:%s\n",msg.setstr);
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);
}
/**
 * @brief 处理自定义请求，在这里添加进程通信
 * @param input
 * @return
 */
int parse_and_process(int sock, const char *query_string, const char *input)
{
    /* input存的是请求的数据*/
    //query_string不一定能用的到

    //先处理登录操作
    if(strstr(input, "username=") && strstr(input, "password=")) //判断字符串是否存在
    {
        return handle_login(sock, input);
    }
    //处理求和请求
    else if(strstr(input, "data1=") && strstr(input, "data2="))
    {
        return handle_add(sock, input);
    }
    //处理modbus_get请求
    else if(strncmp(input,"\"modbus_get\"",12)==0)
    {
        return handler_get(sock,input);
    }
    //处理修改请求
    else if(strstr(input, "led=") || strstr(input, "beep="))
    {
        return handler_set(sock, input);
    }
    else  //剩下的都是json请求，这个和协议有关了
    {
        // 构建要回复的JSON数据
        const char* json_response = "{\"message\": \"Hello, client!\"}";

        // 发送HTTP响应给客户端
        send(sock, json_response, strlen(json_response), 0);
    }
    return 0;
}
