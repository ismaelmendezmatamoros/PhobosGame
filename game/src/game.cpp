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

//////////
    auto mm = EngineBaseInterface::getInstance()->getGraphicsComponent()->getGPUMemoryManager();
    auto p = mm->createBuffer(1, Phobos::BufferType::ArrayBuffer, 400);
    mm->deleteBuffer(1);
////////////////

    GameFSM::init(fsm);
}