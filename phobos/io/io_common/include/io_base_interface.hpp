#pragma once

#include "window.hpp"
#include "io_definitions.hpp"
#include "device_base_interface.hpp"

#include <map>
#include <memory>
#include <list>
#include <optional>

namespace Phobos::Io {

    class IoBaseInterface : public Phobos::Engine::EngineComponent {
        public:

        IoBaseInterface(
                const std::string &name,
                const IoConfiguration &config,
                Phobos::Window::Window &window);
        virtual ~IoBaseInterface() = default;

        void initialize() override;
        void execute() override = 0;
        virtual void readInput() = 0;

        virtual bool refreshDevices() = 0;
        


        Phobos::Io::Device::DeviceBaseInterface* getDevice(IdType deviceId);
        std::list<IdType> getDeviceIds();


        protected:
        IoConfiguration configuration;
        Phobos::Window::Window &windowComponent;
        std::map<IdType, std::unique_ptr<Phobos::Io::Device::DeviceBaseInterface>> devicesMap;
    };

}
