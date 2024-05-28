#ifndef SERVER_H
#define SERVER_H

#include <stddef.h>
#include "config.h"



void start_server(struct server_config *config);
void handle_request(int client_fd, struct server_config *config);

#endif // SERVER_H