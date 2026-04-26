#pragma once

#include "phobos/common/definitions.hpp"
#include "phobos/common/phobos_class.hpp"
#include <shared_mutex>

namespace Phobos {
    using namespace Phobos::Common;

    class Object : virtual public PhobosClass {

        public:
        
        static const std::map<IdType, Object*> &getObjectsRegistry();

        Object();
        Object(const Object &other);
        Object(Object &&other);
        Object& operator=(const Object &other);
        Object& operator=(Object &&other);

        virtual ~Object() = default;
        
        private:

        static inline std::shared_mutex objectsRegistryMutex;
        static inline std::map<IdType, Object*> objectsRegistry;
        

        static void addToRegistry(Object *object);
        static void removeFromRegistry(Object *object);

    };
};