#include "game_fsm.hpp"

Game::GameFSM::GameFSM() : Phobos::FSM<GameStatesKey, GameSignal>{}
{
    auto initStateAction = [this](GameFSMType *fsm) {this->init(fsm);};
    auto splashScreenStateAction = [this](GameFSMType *fsm) {this->splashScreen(fsm);};
    auto finalizeStateAction = [this](GameFSMType *fsm) {this->finalize(fsm);};

    addState({GameStatesKey::Init, initStateAction});
    addState({GameStatesKey::SplashScreen, splashScreenStateAction});
    addState({GameStatesKey::Finalize, finalizeStateAction});

    addTransition({GameStatesKey::Init, GameSignal::InitFinished, GameStatesKey::SplashScreen});
    addTransition({GameStatesKey::SplashScreen, GameSignal::Finalize, GameStatesKey::Finalize});


}

void Game::GameFSM::init(GameFSMType *fsm)
{
    logMessage("Init Game");
}

void Game::GameFSM::splashScreen(GameFSMType *fsm)
{
    logMessage("splashScreen Game");
}

void Game::GameFSM::finalize(GameFSMType *fsm)
{
    logMessage("Finalize Game");
}
