#include "engine.hpp"

namespace Phobos {
namespace Engine {

Engine::Engine(const Configuration config)
        : configuration{config}
        , stopLoop{false}
{
    logMessage("Created", Phobos::LogMessage::SeverityLevel::INFO);
}

Engine::~Engine() {
    stopMainLoop();
    logMessage("Finalizing", Phobos::LogMessage::SeverityLevel::INFO);
}

std::string Engine::formatHeader() const {
    return logHeader;
}

void Engine::initialize()
{
    bool initializeAll = 
            (configuration.initializeComponents & static_cast<InitializeComponentEnumType>(InitializeComponentEnum::All)) != 0;
    bool initializeWindow = configuration.initializeComponents & static_cast<InitializeComponentEnumType>(InitializeComponentEnum::Window);
    if (initializeAll || initializeWindow) {
        window = std::make_unique<Phobos::Window::Window>(configuration.windowConfiguration);
        window->initialize();
    }
}

void Engine::mainLoop() {
    while(!stopLoop.load()) {
        if (window.get() != nullptr) window->execute();
    }
}

void Engine::stopMainLoop() {
    stopLoop.store(true);
}

} // namespace Engine
} // namespace Phobos
