#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "config.h"

int parse_config(const char *config_file, struct server_config *config) {
    FILE *file = fopen(config_file, "r");
    if (!file) {
        perror("fopen");
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, " \t\n");
        char *value = strtok(NULL, " \t\n");

        if (strcmp(key, "listen") == 0) {
            config->port = atoi(value);
        } else if (strcmp(key, "root") == 0) {
            strncpy(config->root, value, sizeof(config->root) - 1);
        } 
    }

    fclose(file); // 确保在返回前关闭文件
    return 0;
}