#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include "request.h"
#include "response.h"
#include "config.h"
void handle_request(int client_fd, struct server_config *config) {
    printf("开始接受请求\n");
    char buffer[1024];
    ssize_t bytes_read;

    bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        return;
    }
    buffer[bytes_read] = '\0';
    printf("请求处理完毕\n");

    // 解析请求并生成响应
    // ...
    const char *response_body = "<html><body><h1>Hello, I'm Heng</h1></body></html>";
    printf("Server configuration:\nPort: %d\nRoot directory: %s\n", config->port, config->root);

        // 调用 send_response 函数发送响应
    send_response(client_fd, config, response_body);
    


}