#pragma once
#include <glm/glm.hpp>

struct RenderSettings {
    glm::vec4 triangleColor = {1.0f, 0.0f, 0.0f, 1.0f};

    RenderSettings() { reset(); }

    void reset() {
        triangleColor = {1.0f, 0.0f, 0.0f, 1.0f};
    }
};