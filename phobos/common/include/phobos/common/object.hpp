#pragma once

#include "phobos/common/definitions.hpp"
#include "phobos/common/phobos_class.hpp"

namespace Phobos {
    using namespace Phobos::Common;

    class Object : virtual public PhobosClass {
        public:
        Object() = default;
        virtual ~Object() = default;

    };

};