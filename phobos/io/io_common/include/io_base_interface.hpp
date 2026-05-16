#pragma once

#include "window.hpp"
#include "io_definitions.hpp"
#include "device_base_interface.hpp"

#include <map>
#include <memory>

namespace Phobos::Io {

    class IoBaseInterface : public Phobos::Engine::EngineComponent {
        public:

        IoBaseInterface(
                const std::string &name,
                const IoConfiguration &config,
                Phobos::Window::Window &window);
        
        void initialize() override;
        void execute() override = 0;
        virtual void readInput() = 0;

        virtual ~IoBaseInterface() = default;

        protected:
        IoConfiguration configuration;
        Phobos::Window::Window &windowComponent;
        std::map<IdType, std::unique_ptr<Phobos::Io::Device::DeviceBaseInterface>> devicesMap;
    };

}
