#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "response.h"

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_read > 0) {
        // 这里可以添加解析HTTP请求的逻辑，但为了简洁，我们直接发送响应
        send_response(client_socket);
    }
}