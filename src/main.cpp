#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "server.hpp"
#include "client.hpp"


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
    
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Window!", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    //test by setting color
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f); // Set clear color to blue
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();


    return 0;
}
