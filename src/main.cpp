#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "server.hpp"
#include "client.hpp"
#include "game.hpp"


int main(int, char**){
    std::cout << "Run a server or a client?\n> ";
    std::string response;
    std::cin >> response;
    if (response == "server" || response == "s") {
        std::cout << "Server incoming\n";
        Server server = Server();
        server.run();
        return 0;
    } else if (response == "client" || response == "c") {
        std::cout << "Client incoming\n";
        Client client = Client();
        return 0;
    } else {
        std::cout << "Here's some rendering\n";
    }
    
    Game game = Game();
    while (game.is_running()) {
        game.run();
    }
}