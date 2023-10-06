#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    char response[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>";

    // 从客户端读取请求
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("读取请求失败");
        return;
    }
    buffer[bytes_read] = '\0';

    // 打印请求内容
    printf("收到请求:\n%s\n", buffer);

    // 发送响应给客户端
    ssize_t bytes_written = write(client_socket, response, strlen(response));
    if (bytes_written == -1) {
        perror("发送响应失败");
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len;

    // 创建套接字
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("创建套接字失败");
        exit(1);
    }

    // 设置地址重用
    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        perror("设置地址重用失败");
        exit(1);
    }

    // 绑定地址
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("绑定地址失败");
        exit(1);
    }

    // 启动监听
    if (listen(server_socket, 10) == -1) {
        perror("启动监听失败");
        exit(1);
    }

    printf("服务器已启动，监听端口 %d\n", PORT);

    // 接受连接并处理请求
    while (1) {
        client_address_len = sizeof(client_address);
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) == -1) {
            perror("接受连接失败");
            continue;
        }

        printf("接受新连接\n");

        // 处理请求
        handle_request(client_socket);
        
        // 关闭客户端套接字
        close(client_socket);
        
        printf("连接已关闭\n");
    }

    // 关闭服务器套接字
    close(server_socket);

    return 0;
}
