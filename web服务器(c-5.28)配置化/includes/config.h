#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>

struct server_config {
    int port;
    char root[1024];
};

int parse_config(const char *config_file, struct server_config *config);

#endif // CONFIG_H