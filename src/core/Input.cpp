#include "Input.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <algorithm>
#include <backends/imgui_impl_glfw.h>

std::array<uint8_t, Input::MaxKeys> Input::s_down{};
std::array<uint8_t, Input::MaxKeys> Input::s_pressed{};
std::array<uint8_t, Input::MaxKeys> Input::s_released{};

std::array<uint8_t, Input::MaxMouse> Input::s_mdown{};
std::array<uint8_t, Input::MaxMouse> Input::s_mpressed{};
std::array<uint8_t, Input::MaxMouse> Input::s_mreleased{};

double Input::s_mouseX = 0.0;
double Input::s_mouseY = 0.0;
double Input::s_prevMouseX = 0.0;
double Input::s_prevMouseY = 0.0;
bool Input::s_hasPrevMouse = false;

double Input::s_scrollX = 0.0;
double Input::s_scrollY = 0.0;

void Input::attach(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Initialize cursor position once
    glfwGetCursorPos(window, &s_mouseX, &s_mouseY);
    s_prevMouseX = s_mouseX;
    s_prevMouseY = s_mouseY;
    s_hasPrevMouse = true;
}

void Input::newFrame() {
    s_pressed.fill(0);
    s_released.fill(0);
    s_mpressed.fill(0);
    s_mreleased.fill(0);

    s_scrollX = 0.0;
    s_scrollY = 0.0;

    s_prevMouseX = s_mouseX;
    s_prevMouseY = s_mouseY;
}

bool Input::keyDown(int key) {
    if (key < 0 || key >= MaxKeys) return false;
    return s_down[key] != 0;
}
bool Input::keyPressed(int key) {
    if (key < 0 || key >= MaxKeys) return false;
    return s_pressed[key] != 0;
}
bool Input::keyReleased(int key) {
    if (key < 0 || key >= MaxKeys) return false;
    return s_released[key] != 0;
}

bool Input::mouseDown(int button) {
    if (button < 0 || button >= MaxMouse) return false;
    return s_mdown[button] != 0;
}
bool Input::mousePressed(int button) {
    if (button < 0 || button >= MaxMouse) return false;
    return s_mpressed[button] != 0;
}
bool Input::mouseReleased(int button) {
    if (button < 0 || button >= MaxMouse) return false;
    return s_mreleased[button] != 0;
}

double Input::mouseX() { return s_mouseX; }
double Input::mouseY() { return s_mouseY; }
double Input::mouseDX() { return s_hasPrevMouse ? (s_mouseX - s_prevMouseX) : 0.0; }
double Input::mouseDY() { return s_hasPrevMouse ? (s_mouseY - s_prevMouseY) : 0.0; }

double Input::scrollX() { return s_scrollX; }
double Input::scrollY() { return s_scrollY; }

void Input::keyCallback(GLFWwindow* w, int key, int sc, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(w, key, sc, action, mods); 
    if (key < 0 || key >= MaxKeys) return;

    if (action == GLFW_PRESS) {
        if (!s_down[key]) s_pressed[key] = 1;
        s_down[key] = 1;
    } else if (action == GLFW_RELEASE) {
        s_down[key] = 0;
        s_released[key] = 1;
    }
    // GLFW_REPEAT: keep s_down true, don't set pressed again
}

void Input::mouseButtonCallback(GLFWwindow* w, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(w, button, action, mods);
    if (button < 0 || button >= MaxMouse) return;

    if (action == GLFW_PRESS) {
        if (!s_mdown[button]) s_mpressed[button] = 1;
        s_mdown[button] = 1;
    } else if (action == GLFW_RELEASE) {
        s_mdown[button] = 0;
        s_mreleased[button] = 1;
    }
}

void Input::cursorPosCallback(GLFWwindow* w, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(w, xpos, ypos);
    s_mouseX = xpos;
    s_mouseY = ypos;
    if (!s_hasPrevMouse) {
        s_prevMouseX = xpos;
        s_prevMouseY = ypos;
        s_hasPrevMouse = true;
    }
}

void Input::scrollCallback(GLFWwindow* w, double xoffset, double yoffset) {
    ImGui_ImplGlfw_ScrollCallback(w, xoffset, yoffset); 
    s_scrollX += xoffset;
    s_scrollY += yoffset;
}
