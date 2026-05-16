#pragma once

#include "window.hpp"
#include "io_definitions.hpp"

namespace Phobos::Io {

    class IoBaseInterface : public Phobos::Engine::EngineComponent {
        public:

        IoBaseInterface(
                const std::string &name,
                const IoConfiguration &config,
                Phobos::Window::Window &window);
        
        void initialize() override;
        void execute() override;
        virtual void readInput() = 0;

        virtual ~IoBaseInterface() = default;

        private:

        IoConfiguration configuration;
        Phobos::Window::Window &windowComponent;
    };

}