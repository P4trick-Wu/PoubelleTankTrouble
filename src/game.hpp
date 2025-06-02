#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_tools.hpp"


class Game {
    public:
        Game();
        ~Game();
        void run();
        bool is_running();

    private:
        GLFWwindow* window;
        GLuint shader_program;
        GLuint vao;
        GLuint vbo;
        bool running;
};

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

#endif