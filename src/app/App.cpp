#include "App.h"

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gfx/Renderer.h"
#include "ui/ImGuiLayer.h"

static void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << "\n";
}

App::App(int width, int height, const std::string& title)
    : m_width(width), m_height(height) {

    initGLFW();
    createWindow(width, height, title);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    initGLAD();

    // Print version
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << "\n";
}

App::~App() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

void App::initGLFW() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW");
    }

    // Keep this as 3.3 core for maximum compatibility (ImGui happy too)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void App::createWindow(int width, int height, const std::string& title) {
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
}

void App::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to init GLAD");
    }
}

void App::run() {
    Renderer renderer;
    renderer.init(); // creates VAO/VBO + loads shaders

    ImGuiLayer imgui;
    imgui.init(m_window, "#version 330 core");

    while (!glfwWindowShouldClose(m_window)) {

        glClearColor(0.1f, 0.12f, 0.16f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 1) draw your scene
        renderer.render();

        // 2) draw UI last
        imgui.beginFrame();
        imgui.drawDemo(); // or your own windows
        imgui.endFrame();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    // Important: shutdown while context still exists
    imgui.shutdown();
    renderer.shutdown();
}

void App::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    auto* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->onResize(width, height);
    }
}

void App::onResize(int width, int height) {
    m_width = width;
    m_height = height;

    glViewport(0, 0, width, height);
    //m_renderer.onResize(width, height) // send info back to renderer
}
