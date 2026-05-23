#include "io_base_interface.hpp"

namespace Phobos::Io {

IoBaseInterface::IoBaseInterface(
        const std::string &name,
        const IoConfiguration &config,
        Phobos::Window::Window &window)
    : Phobos::Engine::EngineComponent{name}, configuration{config}, windowComponent{window} {
}

void IoBaseInterface::initialize() {
    // Base implementation - can be overridden in subclasses
}



} // namespace Phobos::Io
