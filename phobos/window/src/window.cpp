#include "phobos/window/window.hpp"

namespace phobos::window {

Window::Window(const std::string& title, int width, int height)
    : title(title), width(width), height(height), open(false) {
}

void Window::show() {
    open = true;
}

void Window::hide() {
    open = false;
}

bool Window::isOpen() const {
    return open;
}

} // namespace phobos::window
