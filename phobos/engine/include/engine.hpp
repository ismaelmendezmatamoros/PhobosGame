#pragma once

#include "common.hpp"
#include "window.hpp"
#include "sound.hpp"
#include "io.hpp"
#include "graphics.hpp"

#include "engine_configuration.hpp"

#include <string>
#include <atomic>

namespace Phobos {


class Engine : public Phobos::PhobosClass {
    public:
    
    static std::unique_ptr<Engine> createEngine(const EngineConfiguration config = EngineConfiguration{}); 
    ~Engine();

    virtual std::string formatHeader() const override;

    void initialize();
    void mainLoop();
    void stopMainLoop();
    
    Io::Io *getIoComponent();

    private:
    Engine(const EngineConfiguration config = EngineConfiguration{});

    static constexpr std::string logHeader{"Engine"};
    EngineConfiguration configuration;
    std::unique_ptr<Window::Window> window;
    std::unique_ptr<Io::Io> io;
    std::atomic<bool> stopLoop;
};

} // namespace Phobos
