#include "client.hpp"


Client::Client() {
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    Message message;
    message.data = CLIENT_CONNECT;
    sendto(this->sockfd, &message, sizeof(message), 0, (const struct sockaddr*)&this->server_addr, sizeof(server_addr));

    message.data = CLIENT_ATTEMPT_DISCONNECT;
    sendto(this->sockfd, &message, sizeof(message), 0, (const struct sockaddr*)&this->server_addr, sizeof(server_addr));

    socklen_t len = sizeof(server_addr);
    ssize_t received = recvfrom(this->sockfd, &buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&server_addr, &len);

    if (buffer.data == DISCONNECT_SUCCESS) {
        std::cout << "We have successfuly disconnected\n";
    }
}

Client::~Client() {
    close(this->sockfd);
}