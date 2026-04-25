#include "phobos/common/common.hpp"
#include "phobos/window/window.hpp"
#include "phobos/sound/sound.hpp"
#include "phobos/io/io.hpp"
#include "phobos/graphics/graphics.hpp"

#include <iostream>

int main() {
    std::cout << "=== Phobos Game Engine ===" << std::endl;
    
    try {
        Phobos::Object obj;
        Phobos::Logger::logMessage("szdfsdfsdf");
        obj.logMessage("real shit");
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
