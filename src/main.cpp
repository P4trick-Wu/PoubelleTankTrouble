#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "server.hpp"
#include "client.hpp"


//Forward declarations
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//vertex shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//Fragment shader source code
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

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
    
    //Initialize glfw
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a glfw window and set it to the current context
    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Window!", NULL, NULL);
    if(window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //Set window size to full screen
    glfwMaximizeWindow(window);
    // Tell GLFW to call this function on every window resize by registering
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    //Glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Set size of rendering window
    glViewport(0, 0, 640, 480);

    //build and compile our shader program
    // ---------------------------------------------------
    // vertex shader
    // ---------------------------------------------------
    
    //dynamically compile shader at runtime from its source code
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //attach the shader source code to the shader object and compile the shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //check if shader compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment shader compilation
    // ---------------------------------------------------
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //check if shader compilation was successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Link shaders
    //Create program object, return ID reference to new program object
    unsigned int shaderProgram = glCreateProgram();

    //Attach previously compiled shaders to the program object and link
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //check if linking was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //delete shaders after linking, they are no longer needed
    glDeleteShader(vertexShader);  
    glDeleteShader(fragmentShader);

    // SEt up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f, // bottom right
         0.0f,  0.5f, 0.0f  // top
    };

    //Generate a VAO and VBO 
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Bind the Vertex Array Object first, then bind and set the vertex buffer(s), then
    //configure vertex attributes 
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //note that this is allowed, the call to glVertexAttribPointer registered VBO as 
    //the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO
    glBindVertexArray(0);

    //final linekd version of multiple shaders combined, to a shader program object
    //then active when rendering objects.

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        #pragma region input

        //Check whether user has pressed the escape key
        processInput(window);

        #pragma endregion

        // ..:: Drawing code (in render loop) :: ..
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color 
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        //Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // 1 triangle

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate all resources 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

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

