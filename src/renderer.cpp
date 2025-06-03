#include "renderer.hpp"


Renderer::Renderer() {
    this->triangles = Array<Triangle>();
    this->shader_program = 0;
    this->vao = 0;
    this->vbo = 0;
}

Renderer::Renderer(GLuint shader_program, GLuint vao, GLuint vbo) {
    this->triangles = Array<Triangle>();
    this->shader_program = shader_program;
    this->vao = vao;
    this->vbo = vbo;
}

void Renderer::sketch_triangle(Triangle* tri) {
    Triangle sketch;
    sketch.p1 = tri->p1;
    sketch.p2 = tri->p2;
    sketch.p3 = tri->p3;
    sketch.color = tri->color;
    this->triangles += sketch;
}

void Renderer::execute_draw() {
    float data_buffer[this->triangles.get_size() * 6];
    for (uint32_t i = 0; i < this->triangles.get_size(); i++) {
        data_buffer[(i * 6)] = this->triangles[i].p1.x;
        data_buffer[(i * 6) + 1] = this->triangles[i].p1.y;
        data_buffer[(i * 6) + 2] = this->triangles[i].p2.x;
        data_buffer[(i * 6) + 3] = this->triangles[i].p2.y;
        data_buffer[(i * 6) + 4] = this->triangles[i].p3.x;
        data_buffer[(i * 6) + 5] = this->triangles[i].p3.y;
    }
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, this->triangles.get_size() * 6 * sizeof(float), data_buffer, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(this->shader_program);
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->triangles.get_size() * 3);

    this->triangles.clear();
}