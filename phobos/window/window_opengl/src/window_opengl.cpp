#include "window_opengl.hpp"
#include <format>

using namespace Phobos::Window::OpenGL;

WindowOpenGL::WindowOpenGL(Window::WindowConfiguration config) : WindowBaseInterface{config}
{
    logMessage(std::format("Window \"{}\" created", title), LogMessage::SeverityLevel::INFO);
}

void WindowOpenGL::show()
{
}

void WindowOpenGL::hide()
{
}

void WindowOpenGL::close()
{
}

bool WindowOpenGL::getFullScreen() const
{
    return true;
}

bool WindowOpenGL::setFullScreen()
{
    return false;
}

Phobos::Window::Resolution WindowOpenGL::getResolution() const
{
    return Phobos::Window::Resolution{};
}

std::string WindowOpenGL::formatHeader() const {
    return logHeader;
}

void WindowOpenGL::setResolution(const Resolution &newResolution)
{
    (void)newResolution;
}

void WindowOpenGL::refresh()
{
}
