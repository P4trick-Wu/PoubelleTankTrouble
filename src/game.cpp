#include "game.hpp"


Game::Game() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(640, 480, "Window!", NULL, NULL);
    if (this->window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->window);
    glfwMaximizeWindow(this->window);

    glfwSetFramebufferSizeCallback(this->window, frame_buffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }
    // Set size of rendering window
    glViewport(0, 0, 640, 480);

    // Compile shaders
    this->shader_program = create_shader_program("../src/shaders/triangle.vert", "../src/shaders/triangle.frag");

    // Generate a VAO and VBO 
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);

    this->running = true;
}

Game::~Game() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteProgram(this->shader_program);
    glfwTerminate();
}

void Game::run() {
    // Poll inputs
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        this->running = false;
    }

    // ..:: Drawing code (in render loop) :: ..
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color 
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    float vertices[] = {
        // positions
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f, // bottom right
         0.0f,  0.5f, 0.0f  // top
    };

    // Bind the Vertex Array Object first, then bind and set the vertex buffer(s), then
    // configure vertex attributes 
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //note that this is allowed, the call to glVertexAttribPointer registered VBO as 
    //the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO
    glBindVertexArray(0);

    //final linekd version of multiple shaders combined, to a shader program object
    //then active when rendering objects.

    //Draw the triangle
    glUseProgram(this->shader_program);
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3); // 1 triangle

    // Check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Game::is_running() {
    return this->running;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}