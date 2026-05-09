#pragma once

#include "common.hpp"
#include "windows_definitions.hpp"

#include <string>
#include <string_view>

namespace Phobos::Window {

    class WindowBaseInterface : public PhobosClass {
        public:
        WindowBaseInterface(Window::WindowConfiguration config)
            : title{config.title}, opened{true} {
            }
        virtual ~WindowBaseInterface() = default;
        
        virtual void show() = 0;
        virtual void hide() = 0;
        virtual bool isOpen() const { return opened; }
        virtual void close() = 0;
        virtual bool getFullScreen() const = 0;
        virtual bool setFullScreen() = 0;

        virtual Resolution getResolution() const = 0;
        virtual void setResolution(const Resolution &newResolution) = 0;

        virtual void refresh() = 0;

        std::string formatHeader() const override= 0;

        std::string getTitle() const { return title; }
        void setTitle(std::string_view newTitle) { title = std::string(newTitle); }


            
        protected:
            std::string title;
            bool opened;
            WindowConfiguration configuration;
    };
}


