#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <event.h>

void handle_request(int sock, short event, void *arg) {
    char buffer[4096];
    ssize_t bytes_read;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 接收客户端请求
    bytes_read = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &client_len);
    if (bytes_read <= 0) return;

    // 处理GET请求，简单示例只考虑静态文件服务
    char* method_end = strstr(buffer, " HTTP/1.");
    if (method_end && strncmp(buffer, "GET ", 4) == 0) {
        *method_end = '\0'; // 截断请求行
        strcat(buffer, "html"); // 简单假设所有请求都映射到index.html，实际应根据路径处理
        FILE* file = fopen(buffer + 4, "rb"); // 跳过"GET "
        if (file) {
            fseek(file, 0, SEEK_END);
            long length = ftell(file);
            fseek(file, 0, SEEK_SET);

            char* content = malloc(length + 1);
            fread(content, 1, length, file);
            content[length] = '\0';
            fclose(file);

            // 构建响应头
            char response[4096];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/html\r\n"
                     "Content-Length: %ld\r\n"
                     "\r\n", length);
            send(sock, response, strlen(response), 0);
            send(sock, content, length, 0);
            free(content);
        } else {
            // 文件未找到或其他错误
            const char* not_found = "HTTP/1.1 404 Not Found\r\n\r\nFile Not Found";
            send(sock, not_found, strlen(not_found), 0);
        }
    }

    close(sock);
}

int main() {
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // 端口
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(listen_sock, 5) < 0) {
        perror("listen");
        return 1;
    }

    struct event_base* base = event_base_new();
    struct event* ev = evconnlistener_new_bind(base, handle_request, NULL,
                                             LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                             (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (!ev) {
        perror("evconnlistener_new_bind");
        return 1;
    }

    event_base_dispatch(base);

    evconnlistener_free(ev);
    event_base_free(base);
    close(listen_sock);

    return 0;
}