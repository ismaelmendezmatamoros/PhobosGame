#include "engine.hpp"

#include <iostream>
#include <functional>
#include <csignal>
#include <any>

Phobos::Engine::Engine *enginePtr;

void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "\nCtrl+C capturado. Cerrando...\n";
        if (enginePtr != nullptr) {
            enginePtr->stopMainLoop();
        }
    }
}

class KbObserver: public Phobos::Io::KeyMapperBaseInterface {
    protected:
        std::any mapKeys(const std::map<int, Phobos::Io::DeviceElementDescriptor> &nativeKeys) override {
            if(nativeKeys.contains(static_cast<int>(Phobos::Io::KeyBoardKeyType::Key_Q))
                    && std::get<Phobos::Io::KeyStatus>(nativeKeys.at(static_cast<int>(Phobos::Io::KeyBoardKeyType::Key_Q))) == Phobos::Io::KeyStatus::Released) {
                std::cout<< "asdafasdf"<<std::endl;
            } else {
                //std::cout<< "NOO"<<std::endl;
            }
            return std::make_any<int>(7);
        }
};

int main() {
    try {
        Engine::Configuration conf{};
        conf.windowConfiguration.title = "GAME";

        auto engine = Phobos::Engine::Engine(conf);

        enginePtr = &engine;
        std::signal(SIGINT, signal_handler);

        engine.initialize();
        Phobos::Io::Io* io = engine.getIoComponent();
        auto kbId = io->getDeviceIds().front();
        auto kbDevice = io->getDevice(kbId);
        kbDevice->emplaceKeyMapper<KbObserver>();
        
        engine.mainLoop();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
