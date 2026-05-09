#pragma once

#include <string>

namespace phobos::sound {

class SoundManager {
public:
    SoundManager();
    ~SoundManager() = default;
    
    void initialize();
    void shutdown();
    bool isInitialized() const;
    
private:
    bool initialized;
};

} // namespace phobos::sound
