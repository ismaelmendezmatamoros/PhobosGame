#include "phobos/common/common.hpp"
#include "phobos/window/window.hpp"
#include "phobos/sound/sound.hpp"
#include "phobos/io/io.hpp"
#include "phobos/graphics/graphics.hpp"

#include <iostream>

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

    }

    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
