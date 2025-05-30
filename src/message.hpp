#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>

#define CLIENT_CONNECT 0
#define CLIENT_ATTEMPT_DISCONNECT 1
#define DISCONNECT_SUCCESS 2


struct Message {
    uint8_t data;
};

#endif