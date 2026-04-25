#pragma once

#include <string>

namespace phobos::window {

class Window {
public:
    Window(const std::string& title = "Phobos Window", int width = 800, int height = 600);
    ~Window() = default;
    
    void show();
    void hide();
    bool isOpen() const;
    
private:
    std::string title;
    int width;
    int height;
    bool open;
};

} // namespace phobos::window
