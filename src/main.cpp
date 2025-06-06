#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "server.hpp"
#include "client.hpp"


//Forward declarations
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

    //Initialize glfw, GLAD and create a window
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Window!", NULL, NULL);
    if(window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        std::cerr << glfwGetError(NULL) << "\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwMaximizeWindow(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set size of rendering window
    glViewport(0, 0, 640, 480);

    // Tell GLFW to call this function on every window resize by registering
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    //test by setting color

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        #pragma region input

        //Check whether user has pressed the escape key
        processInput(window);

        #pragma endregion

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up, delete all GLFW's resources that were allocated and close the window
    glfwTerminate();
    return 0;
}

/*
Funcion to process input from user
*/
void processInput(GLFWwindow *window) {

    //Takes the window as input together with key to check whether the key is being pressed.
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

/*
Callback function to adjust the viewport whenever the window is resized
*/
void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
