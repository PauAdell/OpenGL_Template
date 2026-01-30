#pragma once
#include <glad/glad.h>
#include <memory>
#include "../core/RenderSettings.h"

class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void render(const RenderSettings& renderSettings, float time);
    void shutdown();

private:
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    std::unique_ptr<Shader> m_shader;
};
