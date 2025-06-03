#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle.hpp"
#include "templates/array.hpp"


class Renderer {
    public:
        Renderer();
        Renderer(GLuint shader_program, GLuint vao, GLuint vbo);
        void sketch_triangle(Triangle* tri);
        void execute_draw();

    private:
        Array<Triangle> triangles;
        GLuint shader_program;
        GLuint vao;
        GLuint vbo;
};

#endif