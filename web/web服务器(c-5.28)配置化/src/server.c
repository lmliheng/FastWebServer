#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"
#include "request.h"
#include "response.h"

void start_server(struct server_config *config) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;

    // 在这里添加调试输出
    printf("Starting server with port: %d\n", config->port);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(1);
        
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(config->port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
       
    }

    if (listen(server_fd, 10) == -1) {
        perror("listen");
        exit(1);
        
    }

    while (1) {
        client_addr_size = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_size);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        // 在这里添加调试输出
        printf("Accepted connection from client: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        handle_request(client_fd, config);



        close(client_fd);
    }
}