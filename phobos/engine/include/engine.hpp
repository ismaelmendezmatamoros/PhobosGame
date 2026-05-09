#pragma once

#include "common.hpp"
#include "window.hpp"
#include "sound.hpp"
#include "io.hpp"
#include "graphics.hpp"

namespace Phobos {
namespace Engine {

class Engine {
public:
    Engine();
    ~Engine();

    void initialize();
};

} // namespace Engine
} // namespace Phobos
