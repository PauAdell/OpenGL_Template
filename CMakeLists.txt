cmake_minimum_required(VERSION 3.16)
project(MyOpenGLTemplate LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: sensible defaults
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# -------------------------
# ImGui (static library)
# -------------------------
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    # optional:
    external/imgui/imgui_demo.cpp

    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
)

# ImGui backends need GLFW + OpenGL symbols
target_include_directories(imgui PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_libraries(imgui PUBLIC ${GLFW_LIBRARIES} OpenGL::GL)

# -------------------------
# Your app
# -------------------------
add_executable(app
    src/main.cpp

    src/app/App.cpp
    src/gfx/Renderer.cpp
    src/gfx/Shader.cpp
    src/ui/ImGuiLayer.cpp
    src/core/Input.cpp

    external/glad/src/glad.c
)

target_include_directories(app PRIVATE
    src
    external/glad/include
    ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(app PRIVATE
    imgui
    ${GLFW_LIBRARIES}
    OpenGL::GL
    dl
    pthread
    glm::glm
)
