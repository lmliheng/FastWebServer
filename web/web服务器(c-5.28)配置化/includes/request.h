#ifndef REQUEST_H
#define REQUEST_H

#include <stddef.h>
#include "config.h"

void handle_request(int client_fd, struct server_config *config);

#endif // REQUEST_H