#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 50227
#define BUFFER_SIZE 1024


class Client {
    public:
            Client();
            ~Client();
    
        private:
            int sockfd;
            struct sockaddr_in server_addr;
            char buffer[BUFFER_SIZE];
};

#endif