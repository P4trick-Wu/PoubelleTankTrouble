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

    this->target_fps = 60;
    this->frame_duration = std::chrono::milliseconds(1000 / target_fps);

    this->renderer = Renderer(this->shader_program, this->vao, this->vbo);
}

Game::~Game() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteProgram(this->shader_program);
    glfwTerminate();
}

void Game::run() {
    auto frame_start = std::chrono::steady_clock::now();
    // Poll inputs
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        this->running = false;
    }
    // Check close window button
    if (glfwWindowShouldClose(window)) {
        this->running = false;
    }

    // ..:: Drawing code (in render loop) :: ..
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color 
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    Color c;
    color_init(&c, 1.0, 1.0, 1.0, 1.0);
    Point p1;
    point_init(&p1, -0.5, -0.5);
    Point p2;
    point_init(&p2, 0.5, -0.5);
    Point p3;
    point_init(&p3, 0.0, 0.5);
    Triangle t;
    triangle_init(&t, p1, p2, p3, c);
    
    this->renderer.sketch_triangle(&t);
    this->renderer.execute_draw();

    // Check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    auto frame_end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start);

    if (elapsed < frame_duration) {
        std::this_thread::sleep_for(frame_duration - elapsed);
    }
}

bool Game::is_running() {
    return this->running;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}