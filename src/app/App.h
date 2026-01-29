#pragma once

#include <string>
struct GLFWwindow;

class App {
public:
    App(int width, int height, const std::string& title);
    ~App();

    void run();
    void onResize(int width, int height);

private:
    void initGLFW();
    void createWindow(int width, int height, const std::string& title);
    void initGLAD();

private:
    GLFWwindow* m_window = nullptr;
    int m_width = 0;
    int m_height = 0;
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
