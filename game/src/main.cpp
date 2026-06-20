#include "engine.hpp"

#include <iostream>
#include <functional>
#include <csignal>
#include <any>

#include "game_fsm.hpp"

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
        std::any mapKeys(const Phobos::Io::DeviceKeysStatus &nativeKeys) override {
            if(nativeKeys.contains(static_cast<int>(Phobos::Io::KeyBoardKeyType::Key_Q))
                    && std::get<Phobos::Io::KeyStatus>(nativeKeys.at(static_cast<int>(Phobos::Io::KeyBoardKeyType::Key_Q))) == Phobos::Io::KeyStatus::Released) {
                std::cout<< "asdafasdf"<<std::endl;
            } else {
                //std::cout<< "NOO"<<std::endl;
            }
            return std::make_any<int>(7);
        }
};



class Pub : public Phobos::Publisher<int>
{
private:
    /* data */
public:
    Pub() {}
    ~Pub() {}
};

class Sub : public Phobos::PhobosClass, public Phobos::Subscriber<int>
{
private:
    /* data */
public:
    Sub() {}
    void onDataReceived(PublisherInterface<int> *publisher, int &data) override {
        std::stringstream ss; 
        ss << "Data from " << data;
        logMessage(ss.str());
    }
    Sub(Sub&&) = default;
    Sub(const Sub&) = default;
    ~Sub() {}
};



int main() {
    try {

        Game::GameFSM game;

        Engine::Configuration conf{};
        conf.windowConfiguration.title = "GAME";

        auto engine = Phobos::Engine::Engine(conf);

        enginePtr = &engine;
        std::signal(SIGINT, signal_handler);

        engine.initialize();
        ///////////////////////////////////

        Phobos::Io::Io* io = engine.getIoComponent();
        auto kbId = io->getDeviceIds().front();
        auto kbDevice = io->getDevice(kbId);
        kbDevice->emplaceKeyMapper<KbObserver>();
        
        //////////////////////////////////

        Pub pub;

        Sub sub;
        sub.subscribe(&pub);
        Sub sub2{std::move(sub)};
        Sub sub3{sub2};
        pub.publishData(8);
        sub2.processPublications();
        sub3.processPublications();

        //pub.clearSubscriptors();
        //sub.unsubscribe(&pub);
        //////////////////////////////////
        engine.mainLoop();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
