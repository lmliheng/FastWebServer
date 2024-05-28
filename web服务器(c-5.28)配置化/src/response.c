#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "response.h"

void send_response(int client_fd, struct server_config *config, const char *response_body) {
    printf("开始发送请求\n"); // 使用 \n 作为换行，并修复双引号
    char response[1024];
    snprintf(response, sizeof(response), // 使用 snprintf 防止缓冲区溢出
             "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n%s",
             strlen(response_body) + 1, // 包括结束的空字符
             response_body);
    write(client_fd, response, strlen(response));
    printf("结束发送请求\n"); // 使用 \n 作为换行，并修复双引号
}