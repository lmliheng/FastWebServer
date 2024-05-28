#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include <sys/socket.h>

void send_response(int client_socket) {
    const char* html_content = "<!DOCTYPE html><html><head<title>Hello from C Web Server</title></head><body><h1>Hello, World!</h1></body></html>";
    char header[512] = {0};

    // 构建HTTP响应头
    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n", strlen(html_content));

    // 发送响应头和内容
    send(client_socket, header, strlen(header), 0);
    send(client_socket, html_content, strlen(html_content), 0);
}

// 在response.h中声明send_response函数
void send_response(int client_socket);