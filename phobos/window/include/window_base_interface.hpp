#pragma once

#include "common.hpp"
#include "windows_definitions.hpp"
#include "engine_component.hpp"

#include <string>
#include <string_view>
#include <glm/vec4.hpp>

namespace Phobos::Window {

    class WindowBaseInterface : public Phobos::Engine::EngineComponent {
        public:
        WindowBaseInterface(std::string name,  Window::WindowConfiguration config)
                : Phobos::Engine::EngineComponent{name}
                , title{config.title}
                , opened{true}
                , clearColor{0.0, 0.0, 0.5, 1.0} {
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

        void execute() override = 0;
        void initialize() override = 0;

        void setClearColor(const glm::vec4 &color) {clearColor = color;}
        glm::vec4 getClearColor() {return clearColor;}

        virtual void refresh() = 0;

        std::string getTitle() const { return title; }
        void setTitle(std::string_view newTitle) { title = std::string(newTitle); }
            
        protected:
            std::string title;
            bool opened;
            glm::vec4 clearColor;
            WindowConfiguration configuration;
    };
}


