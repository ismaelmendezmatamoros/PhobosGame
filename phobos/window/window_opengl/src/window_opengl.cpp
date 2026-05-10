#include "window_opengl.hpp"

#include <format>

using namespace Phobos::Window::OpenGL;

WindowOpenGL::WindowOpenGL(Window::WindowConfiguration config)
        : WindowBaseInterface{componentNameConst, config}
{

}

WindowOpenGL::~WindowOpenGL() {
    close();
}

void WindowOpenGL::show()
{
}

void WindowOpenGL::hide()
{
}

void WindowOpenGL::close()
{
    glfwDestroyWindow(window);
    glfwTerminate();
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

void WindowOpenGL::execute() {
    refresh();
}

void WindowOpenGL::initialize() {
    if (!glfwInit())
    {
        throw std::runtime_error{"Unable to init GLFW"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window =
        glfwCreateWindow(
            configuration.resolution.width,
            configuration.resolution.width,
            configuration.title.c_str(),
            nullptr,
            nullptr);

}

void WindowOpenGL::setResolution(const Resolution &newResolution)
{
    (void)newResolution;
}

void WindowOpenGL::refresh()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}
