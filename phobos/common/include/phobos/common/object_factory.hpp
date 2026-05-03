#pragma once

#include <memory>

#include "phobos/common/definitions.hpp"
#include "phobos/common/object.hpp"

#include <concepts>


namespace Phobos {

    template<DerivedFromObject T>
    class ObjectFactory {
        
        public:
        template <typename ...Args>
        static inline std::shared_ptr<T> createObject(Args ...args) {
            return std::make_shared<T>(std::forward(args)...);
        }
    };
};