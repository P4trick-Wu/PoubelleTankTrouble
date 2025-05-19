#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

//Forward declarations
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(int, char**){
    
    GLFWwindow* window;

    //Initialize glfw, GLAD and create a window
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Window!", NULL, NULL);
    if(window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Rendering setup?
    float vertices[] = {
        // positions
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f, // bottom right
         0.0f,  0.5f, 0.0f  // top
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //dynamically compile shader at runtime from its source doe
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER); 

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

    //compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //check if shader compilation was successful

    //final linekd version of multiple shaders combined, to a shader program object
    //then active when rendering objects.

    //create program object, returns ID reference to new program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

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

    //activate program object
    glUseProgram(shaderProgram);

    //delete shaders after linking, they are no longer needed
    glDeleteShader(vertexShader);  
    glDeleteShader(fragmentShader);

    //tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //generate a VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    //To use, we bind the VAO, then bind VBO's and unbind VAO to alter use?
    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Render loop
    while (!glfwWindowShouldClose(window)) {

        #pragma region input

        //Check whether user has pressed the escape key
        processInput(window);

        #pragma endregion

        // ..:: Drawing code (in render loop) :: ..
        // 4. draw the object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // 1 triangle

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
