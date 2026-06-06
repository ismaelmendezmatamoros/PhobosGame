#pragma once

#include "io_definitions.hpp"
#include <any>

namespace Phobos::Io {
    class ActionListenerBaseInterface {
        
        virtual void processAction(const std::any &action) = 0;
        virtual ~ActionListenerBaseInterface() = default;
    };    
}