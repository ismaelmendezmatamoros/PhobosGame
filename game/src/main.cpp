#include "engine.hpp"

#include <iostream>
#include <functional>
#include <csignal>
#include <any>

#include "game.hpp"

Phobos::Engine *enginePtr;
Game *gameFsm;

void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "\nCtrl+C capturado. Cerrando...\n";
        /*if (enginePtr != nullptr) {
            enginePtr->stopMainLoop();
        }*/
        if (gameFsm != nullptr) {
            gameFsm->signal(static_cast<int>(GameSignal::Finalize));
        }
    }
}

int main() {
    try {

        Phobos::GameFSM game;

        EngineConfiguration conf{};
        conf.windowConfiguration.title = "GAME";

        auto gsfm = std::make_unique<Game>();
        gameFsm = gsfm.get();
        auto engineUnique= Engine::Engine::createEngine(std::move(gsfm), conf);
        auto &engine = *engineUnique;

        enginePtr = &engine;
        std::signal(SIGINT, signal_handler);
        engine.initialize();
        engine.mainLoop();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
