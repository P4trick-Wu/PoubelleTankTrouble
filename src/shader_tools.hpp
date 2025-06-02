#ifndef SHADER_TOOLS_H
#define SHADER_TOOLS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>


std::string load_shader_file(const std::string& path);
GLuint compile_shader(GLenum type, const char* source);
GLuint create_shader_program(const char* vs_src, const char* fs_src);

#endif