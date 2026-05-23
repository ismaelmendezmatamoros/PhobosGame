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

void WindowOpenGL::setClearColor(const glm::vec4 &color) {
    Phobos::Window::WindowBaseInterface::setClearColor(color);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

static WindowOpenGL *self{nullptr};

extern "C" void onWindowResizeCallbackWrapperFunction(GLFWwindow *window, int width, int height) {
    self->onWindowResizeCallback(window, width, height);
};

void WindowOpenGL::initialize() {
    if (!glfwInit())
    {
        throw std::runtime_error{"Unable to init GLFW"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, configuration.resizeable);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window =
        glfwCreateWindow(
            configuration.resolution.width,
            configuration.resolution.width,
            configuration.title.c_str(),
            nullptr,
            nullptr);

    self = this;
    glfwSetWindowSizeCallback(window, onWindowResizeCallbackWrapperFunction);
    glfwMakeContextCurrent(window);
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    
}

void WindowOpenGL::setResolution(const Resolution &newResolution)
{
    (void)newResolution;
}

void WindowOpenGL::onWindowResizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void WindowOpenGL::refresh()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void* WindowOpenGL::getNativeWindow() const {
    return window;
}
