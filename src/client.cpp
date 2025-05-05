#include "client.hpp"


Client::Client() {
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    const char* message = "Hello from client\n";
    sendto(this->sockfd, message, strlen(message), 0, (const struct sockaddr*)&this->server_addr, sizeof(server_addr));

    socklen_t len = sizeof(server_addr);
    ssize_t received = recvfrom(this->sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&server_addr, &len);
    buffer[received] = '\0';
    std::cout << "Server response: " << buffer << "\n";
}

Client::~Client() {
    close(this->sockfd);
}