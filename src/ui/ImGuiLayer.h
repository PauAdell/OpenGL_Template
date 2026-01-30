#pragma once

#include "../core/RenderSettings.h"

struct GLFWwindow;

class ImGuiLayer {
public:
    void init(GLFWwindow* window, const char* glslVersion);
    void beginFrame();
    void endFrame();
    void drawDemo();
    void drawMyDemo(RenderSettings& renderSettings);
    void shutdown();

private:
    bool m_initialized = false;
};
