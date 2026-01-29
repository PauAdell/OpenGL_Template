#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

GLuint Shader::compileStage(GLenum type, const std::string& source, const std::string& debugName) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint logLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        std::vector<char> log(logLen);
        glGetShaderInfoLog(shader, logLen, nullptr, log.data());

        std::cerr << "Shader compile failed (" << debugName << "):\n"
                  << log.data() << "\n";

        glDeleteShader(shader);
        throw std::runtime_error("Shader compile failed: " + debugName);
    }
    return shader;
}

void Shader::linkProgram(GLuint program, GLuint vs, GLuint fs) {
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    GLint ok = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint logLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
        std::vector<char> log(logLen);
        glGetProgramInfoLog(program, logLen, nullptr, log.data());

        std::cerr << "Program link failed:\n" << log.data() << "\n";
        throw std::runtime_error("Program link failed");
    }
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vsrc = readFile(vertexPath);
    std::string fsrc = readFile(fragmentPath);

    GLuint vs = compileStage(GL_VERTEX_SHADER, vsrc, vertexPath);
    GLuint fs = compileStage(GL_FRAGMENT_SHADER, fsrc, fragmentPath);

    m_program = glCreateProgram();
    linkProgram(m_program, vs, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (m_program) glDeleteProgram(m_program);
}

void Shader::use() const {
    glUseProgram(m_program);
}
