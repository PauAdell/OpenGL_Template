#include "app/App.h"
#include <iostream>

int main() {
    try {
        App app(1280, 720, "OpenGL Template");
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
