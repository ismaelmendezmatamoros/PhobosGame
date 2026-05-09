#pragma once

#include "phobos/common/common.hpp"

#include <string>

namespace Phobos::Window {

    class WindowBaseInterface {
        class Window {
        public:
            Window(const std::string& title = "Phobos Window", int width = 800, int height = 600);
            virtual ~Window() = default;
            
            virtual void show() = 0;
            virtual void hide() = 0;
            virtual bool isOpen() const;
            virtual void close() = 0;
            
        private:
            std::string title;
        };
    };
}


