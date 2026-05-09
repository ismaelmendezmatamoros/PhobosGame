#include "window_opengl.hpp"

using namespace Phobos::Window::OpenGL;

WindowOpenGL::WindowOpenGL()
{

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

void WindowOpenGL::setResolution(const Resolution &newResolution)
{
    (void)newResolution;
}

void WindowOpenGL::refresh()
{
}
