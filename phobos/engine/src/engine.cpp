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

    bool initializeIo = window.get() != nullptr 
                            && configuration.initializeComponents & static_cast<InitializeComponentEnumType>(InitializeComponentEnum::Io);
    if (initializeAll || initializeWindow) {
        io = std::make_unique<Phobos::Io::Io>(*window, configuration.ioConfiguration);
        io->initialize();
    }
}

void Engine::mainLoop() {
    Phobos::Timming::TimeStampType now = std::chrono::system_clock::now();
    while(!stopLoop.load()) {
        if (window.get() != nullptr) window->execute();
        if (io.get() != nullptr) io->execute();
    }
}

void Engine::stopMainLoop() {
    stopLoop.store(true);
}

} // namespace Engine
} // namespace Phobos
