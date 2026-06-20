#pragma once

#include "engine.hpp"
#include <memory>

namespace Game {

    enum class GameStatesKey {
        Init = 0,
        SplashScreen,
        Finalize
    };

    
    enum class GameSignal {
        InitFinished = 0,
        Finalize,
        ErrorState,
        Exit
    };
    using GameFSMType = Phobos::FSM<GameStatesKey, GameSignal>;
    class GameFSM : public GameFSMType, Phobos::Object {
        public:

        GameFSM();
        ~GameFSM() = default;

        protected:
        void init(GameFSMType *fsm);
        void splashScreen(GameFSMType *fsm);
        void finalize(GameFSMType *fsm);

        Engine::Configuration conf;
        std::unique_ptr<Engine::Engine> engine;
    };
}