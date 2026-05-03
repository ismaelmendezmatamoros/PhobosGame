#pragma once

#include <concepts>

#include "phobos/common/definitions.hpp"
#include "phobos/common/fsm_state.hpp"

namespace Phobos {
    
    template <typename T>
    class FSM {

        //addState(IdType key, )
        virtual void stateChanged(IdType previousState, IdType newState);
        virtual ~FSM() = default;
    }; 

};