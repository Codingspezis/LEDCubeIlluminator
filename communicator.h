#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <stdint.h>

int initClient(char *addr, int port);
int sendState(uint8_t *data);

#endif // COMMUNICATOR_H
