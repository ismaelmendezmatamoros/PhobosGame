#include "sound.hpp"

namespace phobos::sound {

SoundManager::SoundManager() : initialized(false) {
}

void SoundManager::initialize() {
    initialized = true;
}

void SoundManager::shutdown() {
    initialized = false;
}

bool SoundManager::isInitialized() const {
    return initialized;
}

} // namespace phobos::sound
