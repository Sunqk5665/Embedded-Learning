/***********************************************************************************
Copy right:	    hqyj Tech.
Author:         jiaoyue
Date:           2023.07.01
Description:    http请求处理
***********************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include "custom_handle.h"


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
    else  //剩下的都是json请求，这个和协议有关了
    {
        // 构建要回复的JSON数据
        const char* json_response = "{\"message\": \"Hello, client!\"}";

        // 发送HTTP响应给客户端
        send(sock, json_response, strlen(json_response), 0);
    }

    return 0;
}
