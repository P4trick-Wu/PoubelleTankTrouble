#ifndef GAME_H
#define GAME_H

#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_tools.hpp"
#include "renderer.hpp"


class Game {
    public:
        Game();
        ~Game();
        void run();
        bool is_running();
        int32_t target_fps;
        std::chrono::milliseconds frame_duration;

    private:
        GLFWwindow* window;
        GLuint shader_program;
        GLuint vao;
        GLuint vbo;
        bool running;
        Renderer renderer;
};

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

#endif