#include "engine.hpp"

namespace Phobos {

Engine::Engine(std::unique_ptr<GameFSM> &&gameFSM, const EngineConfiguration config)
        : configuration{config}
        , stopLoop{false}
        , game{std::move(gameFSM)}
{
    logMessage("Created", Phobos::LogMessage::SeverityLevel::INFO);
    Phobos::EngineBaseInterface::engineInstance = this;
}

std::unique_ptr<Engine> Engine::createEngine(std::unique_ptr<GameFSM> &&gameFSM, const EngineConfiguration config)
{
    static std::once_flag onceFlag;
    std::unique_ptr<Engine> createdInstance;
    auto createFunc = [&config, &createdInstance, &gameFSM]() {
        createdInstance = std::unique_ptr<Engine>(new Engine{std::move(gameFSM), config});
    };
    std::call_once(onceFlag, createFunc);
    return createdInstance;
}

Engine::~Engine()
{
    stopMainLoop();
    logMessage("Finalizing", Phobos::LogMessage::SeverityLevel::INFO);
    Phobos::EngineBaseInterface::engineInstance = nullptr;
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

    bool initializeGraphics = graphics.get() != nullptr 
                            && configuration.initializeComponents & static_cast<InitializeComponentEnumType>(InitializeComponentEnum::Graphics);
    if (initializeAll || initializeGraphics) {
        graphics = std::make_unique<Phobos::Graphics::Graphics>();
        graphics->initialize();
    }
}

void Engine::mainLoop() {
    Phobos::Timming::TimeStampType now = std::chrono::system_clock::now();
    while(!stopLoop.load()) {
        if (window.get() != nullptr) window->execute();
        if (io.get() != nullptr) io->execute();
        if (game.get() != nullptr) (*game)();
        if (graphics.get() != nullptr) graphics->execute();
    }
}

void Engine::stopMainLoop() {
    stopLoop.store(true);
}

Io::IoBaseInterface *Engine::getIoComponent()
{
    return io.get();
}

Window::WindowBaseInterface *Engine::getWindowComponent()
{
    return window.get();
}

Graphics::GraphicsBaseInterface *Engine::getGraphicsComponent()
{
    return graphics.get();
}

} // namespace Phobos
