#include "phobos/common/common.hpp"
#include "phobos/window/window.hpp"
#include "phobos/sound/sound.hpp"
#include "phobos/io/io.hpp"
#include "phobos/graphics/graphics.hpp"

#include <iostream>
#include <functional>


        template <Phobos::ValidKey KeyType, typename SignalType, typename CallType, typename ...Args>
        class FSM;

int main() {

    class PP :public Phobos::Object {
        public:
        PP(const int m):Phobos::Object{nullptr}, l{m} {}
        int l;
    };

    std::cout << "=== Phobos Game Engine ===" << std::endl;
    try {
        Phobos::Object obj, parent;
        obj.createChild<PP>(55);
        obj.logMessage( std::format("asdasd {}\n", obj.getChildrenCount()));
        auto childKey = obj.getChildrenIds().front();
        obj.logMessage( std::format("childKey {}\n", obj.getChildrenCount()));
        
        parent.addChild(obj.getChild(childKey));
        obj.logMessage( std::format("parent {}\n", parent.getChildrenCount()));
        parent.createChild<PP>(22);
        obj.logMessage( std::format("obj {}\n", obj.getChildrenCount()));
//        parent.addChild(obj.getChild(obj.getChildrenIds().begin()->getId()));
        for (const auto &p : parent.getChildren()) {
            parent.logMessage(std::format("{}", p->getId()));
        }

        std::function<void(int)> m = [](int l) -> void {std::cout<<"function " << l <<std::endl;};
        m(45);
        auto p = [](int p){std::cout<<"werwer" << p <<std::endl;};

        enum class Signals {    
            STATE1, STATE2, STATE3
        };


        using FSMType = Phobos::FSM<Phobos::IdType, Signals>;

        FSMType::ActionType action1 = [](FSMType *fsm)->int {
            std::cout << "action 1 "<< std::endl;
            fsm->signal(Signals::STATE2);
            return 0;
        };

        FSMType::ActionType action2 = [](FSMType *fsm)->int {
            std::cout << "action 2 " << std::endl;
            fsm->signal(Signals::STATE3);
            return 0;
        };

        FSMType::ActionType action3 = [](FSMType *fsm)->int {
            std::cout << "action 3 "<< std::endl;
            fsm->signal(Signals::STATE1);
            return 0;
        };

        std::list<FSMType::FSMStateTuple> states{{1, action1}, {2, action2}, {3, action3}};
        std::list<FSMType::FSMTransition> transitions{{1, Signals::STATE2, 2}, {2, Signals::STATE3, 3} ,{3, Signals::STATE1, 1}};

        FSMType fsm{1, states, transitions};
        fsm.signal(Signals::STATE1);
        fsm.signal(Signals::STATE1);
        fsm();
        fsm();
        fsm();
        fsm();
        fsm();
        fsm();

        Phobos::Window::Window win;

    }
    

    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
