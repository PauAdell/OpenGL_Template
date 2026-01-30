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
    unsigned int shader = glCreateShader(type);
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

void Shader::linkProgram(unsigned int program, unsigned int vs, unsigned int fs) {
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

    unsigned int vs = compileStage(GL_VERTEX_SHADER, vsrc, vertexPath);
    unsigned int fs = compileStage(GL_FRAGMENT_SHADER, fsrc, fragmentPath);

    ID = glCreateProgram();
    linkProgram(ID, vs, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (ID) glDeleteProgram(ID);
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) std::cerr << "Warning: uniform '" << name << "' not found/used in shader\n";
    glUniform1i(loc, (int) value);
}
void Shader::setInt(const std::string &name, int value) const{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) std::cerr << "Warning: uniform '" << name << "' not found/used in shader\n";
    glUniform1i(loc, value);
}
void Shader::setFloat(const std::string &name, float value) const{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) std::cerr << "Warning: uniform '" << name << "' not found/used in shader\n";
    glUniform1f(loc, value);
}
void Shader::setVec3(const std::string &name, const glm::vec3& value) const{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) std::cerr << "Warning: uniform '" << name << "' not found/used in shader\n";
    glUniform3fv(loc, 1,  &value[0]);
}
void Shader::setVec4(const std::string &name, const glm::vec4& value) const{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) std::cerr << "Warning: uniform '" << name << "' not found/used in shader\n";
    glUniform4fv(loc, 1,  &value[0]);
}
void Shader::setMat4(const std::string &name, const glm::mat4& mat) const{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) std::cerr << "Warning: uniform '" << name << "' not found/used in shader\n";
    glUniformMatrix4fv(loc, 1, GL_FALSE,  &mat[0][0]);
}