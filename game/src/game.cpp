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
    std::string ff{"124"};
    //std::span<const std::byte> raw{(std::byte*)ff.data()};
    p->write(ff, 0);
    auto b = p->read(0, 4);
    std::cout << " sdsd " << (char*) b.data() << std::endl;
    mm->deleteBuffer(1);
    //aqui se testean los buffers
////////////////

    GameFSM::init(fsm);
}