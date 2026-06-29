#pragma once

#include "engine.hpp"


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
/// ///////////////////

class Game: public Phobos::GameFSM {
    public:

    Game() = default;
    void run(Phobos::FSM *fsm) override;
    void init(Phobos::FSM *fsm) override;
    //~GSFM() = default;
};
