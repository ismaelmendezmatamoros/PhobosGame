#pragma once

#include "phobos/common/common.hpp"
#include "phobos/window/windows_definitions.hpp"

#include <string>
#include <string_view>

namespace Phobos::Window {

    class WindowBaseInterface : public PhobosClass {
    public:
        class Window {
        public:
            Window(const std::string& title = "Phobos Window", const Resolution &resolution = {800, 600})
                : title(title), opened(true) {}
            virtual ~Window() = default;
            
            virtual void show() = 0;
            virtual void hide() = 0;
            virtual bool isOpen() const { return opened; }
            virtual void close() = 0;
            virtual bool getFullScreen() const = 0;
            virtual bool setFullScreen() const = 0;

            virtual Resolution getResolution() const = 0;
            virtual void setResolution(const Resolution &newResolution) = 0;

            virtual void refresh() = 0;

            std::string getTitle() const { return title; }
            void setTitle(std::string_view newTitle) { title = std::string(newTitle); }
            
        private:
            std::string title;
            bool opened;
        };
    };
}


