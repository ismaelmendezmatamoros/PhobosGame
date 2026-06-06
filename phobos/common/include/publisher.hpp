#pragma once

#include "definitions.hpp"
#include "subscriber.hpp"
#include <concepts>

namespace Phobos {

    template<std::copy_constructible T>
    class Publisher {
        
    };
}

#include "publisher.icc"