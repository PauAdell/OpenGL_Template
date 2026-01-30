#pragma once

#include <string>
#include "core/RenderSettings.h"

struct GLFWwindow;


class App {
public:
    App(int width, int height, const std::string& title);
    ~App();

    void run();
    void onResize(int width, int height);
    RenderSettings& getRenderSettings() { return m_renderSettings; }
    const RenderSettings& getRenderSettings() const { return m_renderSettings; }

private:
    void initGLFW();
    void createWindow(int width, int height, const std::string& title);
    void initGLAD();
    void processInput(GLFWwindow *window);

    GLFWwindow* m_window = nullptr;
    int m_width = 0;
    int m_height = 0;
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    RenderSettings m_renderSettings;
};
