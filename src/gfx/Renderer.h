#pragma once
#include <glad/glad.h>
#include <memory>

class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void render();
    void shutdown();

private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    std::unique_ptr<Shader> m_shader;
};
