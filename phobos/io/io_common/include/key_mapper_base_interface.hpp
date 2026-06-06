#pragma once

#include <any>
#include <list>

#include "io_definitions.hpp"
#include "phobos_class.hpp"

namespace Phobos::Io
{
    class KeyMapperBaseInterfaceObserver;

    class KeyMapperBaseInterface {
        public:

        /*template<typename T>
        T getMappedData(const Phobos::Io::DeviceElementDescriptor &nativeKeys) {
                return std::any_cast<T>(mapKeys(nativeKeys));
        }*/
        virtual ~KeyMapperBaseInterface() = default;

        public:
            virtual std::any mapKeys(const DeviceKeysStatus &nativeKeys) = 0;
    };

    class KeyMapperBaseInterfaceObserver {
        public:
        virtual void parseKeys(const std::any& action) = 0;
        virtual ~KeyMapperBaseInterfaceObserver() = default;
    };



} // namespace Phobos::
