#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 50227
#define BUFFER_SIZE 1024


class Server {
    public:
        Server();
        ~Server();
        void run();
    
    private:
        int sockfd;
        char buffer[BUFFER_SIZE];
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
};

#endif