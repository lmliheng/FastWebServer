#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"
#include "config.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s<config_file>\n", argv[0]);
        exit(1);
    }

    struct server_config config;
    
    if (parse_config(argv[1], &config) == -1) {
        printf("Error parsing config file.\n");
        exit(1);
    }

    start_server(&config);


    return 0;
}