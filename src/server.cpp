#include "server.hpp"


Server::Server() {
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&this->server_addr, 0, sizeof(this->server_addr));
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = INADDR_ANY;
    this->server_addr.sin_port = htons(PORT);

    bind(this->sockfd, (struct sockaddr*)&this->server_addr, sizeof(this->server_addr));
}

void Server::run() {
    socklen_t len = sizeof(this->client_addr);
    while (true) {
        ssize_t n = recvfrom(this->sockfd, &this->buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&this->client_addr, &len);

        if (buffer.data == CLIENT_CONNECT) {
            std::cout << "Client connect.\n";
        } else if (buffer.data == CLIENT_ATTEMPT_DISCONNECT) {
            std::cout << "Client disconnect.\n";
            Message response;
            response.data = DISCONNECT_SUCCESS;
            sendto(this->sockfd, &response, sizeof(response), 0, (struct sockaddr*)&this->client_addr, len);
        }
    }
}

Server::~Server() {
    close(this->sockfd);
}