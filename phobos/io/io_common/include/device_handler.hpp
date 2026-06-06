#pragma once

#include <list>
#include <memory>


#include "common.hpp"
#include "phobos_class.hpp"

#include "io_definitions.hpp"
#include "key_mapper_base_interface.hpp"
#include "action_listener_base_interface.hpp"

namespace Phobos::Io {
    class DeviceHandler: public PhobosClass {
        public:
        DeviceHandler(const Phobos::Io::DeviceHandler &_device, const Phobos::Io::KeyMapperBaseInterface mapper);
        virtual ~DeviceHandler() = default;

        virtual void processInput();
        void addListener(ActionListenerBaseInterface *listener);
        void removeListener(ActionListenerBaseInterface *listener);
        
        protected:
        const Phobos::Io::DeviceHandler &device;
        std::unique_ptr<Phobos::Io::KeyMapperBaseInterface> mapper;
        std::list<ActionListenerBaseInterface*> listeners;
    };
};