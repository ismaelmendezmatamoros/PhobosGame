#pragma once

#include "window.hpp"

namespace Phobos::Io {

    class IoBaseInterface : Phobos::Engine::EngineComponent {
        public:

        IoBaseInterface(Phobos::Window::Window &window);
        void initialize() override;
        void execute() override;
        void readInput();

    };

}