#pragma once

#include "common.hpp"
#include "window.hpp"
#include "sound.hpp"
#include "io.hpp"
#include "graphics.hpp"
#include "game_fsm.hpp"

#include "engine_configuration.hpp"
#include "engine_base_interface.hpp"

#include <string>
#include <atomic>

namespace Phobos {


class Engine : public Phobos::PhobosClass , public EngineBaseInterface {
    public:
    
    
    static std::unique_ptr<Engine> createEngine(std::unique_ptr<GameFSM> &&gameFSM, const EngineConfiguration config = EngineConfiguration{});
    ~Engine();

    virtual std::string formatHeader() const override;

    void initialize();
    void mainLoop();
    void stopMainLoop() override;


    
    Io::IoBaseInterface *getIoComponent() override; 
    Window::WindowBaseInterface *getWindowComponent() override;

    private:
    Engine(std::unique_ptr<GameFSM> &&gameFSM, const EngineConfiguration config = EngineConfiguration{});

    static constexpr std::string logHeader{"Engine"};
    EngineConfiguration configuration;
    std::unique_ptr<Window::Window> window;
    std::unique_ptr<Io::Io> io;
    std::atomic<bool> stopLoop;
    std::unique_ptr<GameFSM> game;
};

} // namespace Phobos
