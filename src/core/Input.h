#pragma once
#include <array>
#include <cstdint>

struct GLFWwindow;

class Input {
public:
    static void attach(GLFWwindow* window);

    // Call once per frame (at start of frame)
    static void newFrame();

    // Queries
    static bool keyDown(int key);        // currently held
    static bool keyPressed(int key);     // went down this frame
    static bool keyReleased(int key);    // went up this frame

    static bool mouseDown(int button);
    static bool mousePressed(int button);
    static bool mouseReleased(int button);

    static double mouseX();
    static double mouseY();
    static double mouseDX();
    static double mouseDY();

    static double scrollX();
    static double scrollY();

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    static constexpr int MaxKeys = 512;       // enough for GLFW key codes
    static constexpr int MaxMouse = 16;

    static std::array<uint8_t, MaxKeys> s_down;
    static std::array<uint8_t, MaxKeys> s_pressed;
    static std::array<uint8_t, MaxKeys> s_released;

    static std::array<uint8_t, MaxMouse> s_mdown;
    static std::array<uint8_t, MaxMouse> s_mpressed;
    static std::array<uint8_t, MaxMouse> s_mreleased;

    static double s_mouseX, s_mouseY;
    static double s_prevMouseX, s_prevMouseY;
    static bool s_hasPrevMouse;

    static double s_scrollX, s_scrollY;
};
