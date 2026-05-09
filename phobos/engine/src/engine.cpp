#include "engine.hpp"

namespace Phobos {
namespace Engine {

Engine::Engine(const Configuration config)
        : configuration{config} {
    logMessage("Engine created", Phobos::LogMessage::SeverityLevel::INFO);
}

std::string Engine::formatHeader() const {
    return logHeader;
}

Engine::~Engine() = default;

void Engine::initialize()
{
    bool initializeAll = 
            (configuration.initializeComponents & static_cast<InitializeComponentEnumType>(InitializeComponentEnum::All)) != 0;
    bool initializeWindow = configuration.initializeComponents & static_cast<InitializeComponentEnumType>(InitializeComponentEnum::Window);
    if (initializeAll || initializeWindow) {
        std::make_unique<Phobos::Window::Window>(configuration.windowConfiguration);
    }
}

} // namespace Engine
} // namespace Phobos
