#pragma once

#include "common.hpp"
#include "definitions.hpp"
#include "phobos_class.hpp"

#include <memory>

namespace Phobos {

    enum class GameStatesKey : int {
        Init = 0,
        Run,
        Finalize,
        Error
    };

    
    enum class GameSignal : int{
        InitFinished = 0,
        Finalize,
        ErrorState,
        Exit
    };
    class GameFSM : public Phobos::FSM, Phobos::Object {
        public:

        GameFSM();
        ~GameFSM() = default;

        std::string formatHeader() const override;
        
        protected:
        virtual void init(Phobos::FSM *fsm);
        virtual void run(Phobos::FSM *fsm);
        virtual void finalize(Phobos::FSM *fsm);
        virtual void error(Phobos::FSM *fsm);
    };
}