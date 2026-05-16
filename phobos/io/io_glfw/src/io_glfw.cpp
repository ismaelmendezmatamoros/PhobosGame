#include "io_glfw.hpp"
#include <GLFW/glfw3.h>

#include "io_glfw.hpp"

using namespace Phobos::Io::GLFW;

IoGLFW::IoGLFW(Phobos::Window::Window &window, const IoConfiguration &config)
    : IoBaseInterface{componentNameConst, config, window} 
   {}
void IoGLFW::initialize() {}
void IoGLFW::execute() {} 
void IoGLFW::readInput() {}