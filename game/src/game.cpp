#include "game.hpp"

void Game::run(Phobos::FSM *fsm) {
    Pub pub;
    Sub sub;
    sub.subscribe(&pub);
    Sub sub2{std::move(sub)};
    Sub sub3{sub2};
    pub.publishData(8);
    sub2.processPublications();
    sub3.processPublications();
}

void Game::init(Phobos::FSM *fsm) {
    Phobos::Io::IoBaseInterface* io = EngineBaseInterface::getInstance()->getIoComponent();
    auto win = EngineBaseInterface::getInstance()->getWindowComponent();
    win->setClearColor({1.0, 0,0,0});
    auto kbId = io->getDeviceIds().front();
    auto kbDevice = io->getDevice(kbId);
    kbDevice->emplaceKeyMapper<KbObserver>();
    GameFSM::init(fsm);
}