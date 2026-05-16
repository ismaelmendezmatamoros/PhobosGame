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
namespace Engine {

class Engine : public Phobos::PhobosClass {
    public:
    Engine(const Configuration config = Configuration{});
    ~Engine();

    virtual std::string formatHeader() const override;

    void initialize();
    void mainLoop();
    void stopMainLoop();

    private:

    static constexpr std::string logHeader{"Engine"};
    Configuration configuration;
    std::unique_ptr<Window::Window> window;
    std::unique_ptr<Io::Io> io;
    std::atomic<bool> stopLoop;
};

} // namespace Engine
} // namespace Phobos
