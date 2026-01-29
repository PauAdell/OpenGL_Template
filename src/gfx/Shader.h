#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
public:
    // Loads, compiles, links
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void use() const;
    GLuint id() const { return m_program; }

private:
    GLuint m_program = 0;

    static std::string readFile(const std::string& path);
    static GLuint compileStage(GLenum type, const std::string& source, const std::string& debugName);
    static void linkProgram(GLuint program, GLuint vs, GLuint fs);
};
