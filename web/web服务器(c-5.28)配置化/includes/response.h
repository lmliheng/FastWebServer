#ifndef RESPONSE_H
#define RESPONSE_H

#include <stddef.h>
#include "config.h"

void send_response(int client_fd, struct server_config *config, const char *response_body);

#endif // RESPONSE_H