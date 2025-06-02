#include "shader_tools.hpp"


std::string load_shader_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint compile_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    std::string vertex_src = load_shader_file(source);
    const char* vertex_cstr = vertex_src.c_str();

    glShaderSource(shader, 1, &vertex_cstr, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader Compile Error: " << log << "\n";
    }
    return shader;
}

GLuint create_shader_program(const char* vs_src, const char* fs_src) {
    GLuint vertexShader = compile_shader(GL_VERTEX_SHADER, vs_src);
    GLuint fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fs_src);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "Shader Link Error: " << log << "\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}