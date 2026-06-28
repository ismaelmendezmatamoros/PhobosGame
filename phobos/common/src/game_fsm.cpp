#include "game_fsm.hpp"

Phobos::GameFSM::GameFSM() : Phobos::FSM{}
{
    auto initStateAction = [this](Phobos::FSM *fsm, std::any&) {this->init(fsm);};
    auto splashScreenStateAction = [this](Phobos::FSM *fsm, std::any&) {this->run(fsm);};
    auto finalizeStateAction = [this](Phobos::FSM *fsm, std::any&) {this->finalize(fsm);};
    auto errorStateAction = [this](Phobos::FSM *fsm, std::any&) {this->error(fsm);};

    addState({static_cast<int>(GameStatesKey::Init), initStateAction});
    addState({static_cast<int>(GameStatesKey::Run), splashScreenStateAction});
    addState({static_cast<int>(GameStatesKey::Finalize), finalizeStateAction});
    addState({static_cast<int>(GameStatesKey::Error), errorStateAction});

    addTransition({static_cast<int>(GameStatesKey::Init), static_cast<int>(GameSignal::InitFinished), static_cast<int>(GameStatesKey::Run)});
    addTransition({static_cast<int>(GameStatesKey::Run), static_cast<int>(GameSignal::Finalize), static_cast<int>(GameStatesKey::Finalize)});
    
}

std::string Phobos::GameFSM::formatHeader() const
{
    return "Game";
}

void Phobos::GameFSM::init(Phobos::FSM *fsm)
{
    logMessage("Init Game");
}

void Phobos::GameFSM::run(Phobos::FSM *fsm)
{
    logMessage("splashScreen Game");
}

void Phobos::GameFSM::finalize(Phobos::FSM *fsm)
{
    logMessage("Finalize Game");
}

void Phobos::GameFSM::error(Phobos::FSM *fsm)
{
    logMessage("Error Game");
}
