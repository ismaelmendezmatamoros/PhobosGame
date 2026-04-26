#pragma once

#include "phobos/common/definitions.hpp"
#include "phobos/common/phobos_class.hpp"

#include <shared_mutex>
#include <memory>
#include <map>
#include <ranges>

namespace Phobos {
    using namespace Phobos::Common;

    class Object : virtual public PhobosClass {

        public:
        
        static const std::map<IdType, Object*> &getObjectsRegistry();

        Object(std::shared_ptr<Object> parent = std::shared_ptr<Object>{});
        Object(const Object &other);
        Object(Object &&other);
        Object& operator=(const Object &other);
        Object& operator=(Object &&other);

        bool deleteChild(IdType childId);
        void addChild(std::shared_ptr<Object> child);
        std::size_t getChildrenCount() const;
        std::shared_ptr<Object> getChild(IdType childId) const;
        auto getChildren();
        auto getChildrenIds();  
        
        /*vas por qui. lka has cagado con el diseño y a hora de crear un object el padre los almacena como shared pointer
        pero no tienes shared pointer (en los constructores y asignaciones de copia y movimiento). solo puinterop normal asiq hay q cambiarlo. hay que hacer:
        - que el hijo lo cree el padre. de esta forma el padre crea el shared pointer.*/

        virtual ~Object() = default;
        
        private:
        static inline std::shared_mutex objectsRegistryMutex;
        static inline std::map<IdType, Object*> objectsRegistry;
        static void addToRegistry(Object *object);
        static void removeFromRegistry(Object *object);

        mutable std::shared_mutex childrenMutex;
        std::map<IdType, std::shared_ptr<Object>> children;

        std::weak_ptr<Object> parent;
    };
};