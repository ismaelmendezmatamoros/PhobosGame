#pragma once

#include "definitions.hpp"
#include "phobos_class.hpp"

#include <shared_mutex>
#include <memory>
#include <map>
#include <ranges>
#include <concepts>
#include <list>

namespace Phobos {
    using namespace Phobos;

    class Object;

    template <typename Derived>
    concept DerivedFromObject =
    std::derived_from<Derived, Object>;

    class Object : virtual public PhobosClass {



        public:

        static const std::map<IdType, Object*> &getObjectsRegistry();

        Object(Object *parent = nullptr);

        template <DerivedFromObject T, typename ...Args>
        T* createChild(Args&& ...args);

        bool deleteChild(IdType childId);
        std::size_t getChildrenCount() const;
        Object* getChild(IdType childId) const;
        void addChild(Object *child);

        std::list<Object*> getChildren() const;
        std::list<IdType> getChildrenIds() const;

        virtual ~Object() = default;
        
        private:

        Object(const Object &other);
        Object(Object &&other);
        Object& operator=(const Object &other);
        Object& operator=(Object &&other);

        static inline std::shared_mutex objectsRegistryMutex;
        static inline std::map<IdType, Object*> objectsRegistry;
        static void addToRegistry(Object *object);
        static void removeFromRegistry(IdType ObjectId);

        mutable std::shared_mutex childrenMutex;
        std::map<IdType, std::unique_ptr<Object>> children;

        //std::weak_ptr<Object> parent;
        Object *parent;
    };

    template <DerivedFromObject T, typename ...Args> //!!!!!!!!!!!!!!!!!!!!!!!!vas por aqui estas usando unique_ptrs y q el padre cree los hijos
    T* Object::createChild(Args&& ...args) {
        auto child = std::make_unique<T>(std::forward<Args>(args)...);//new T{std::forward<Args>(args)...};
        child->parent = this;
        auto it = children.insert_or_assign(child->getId(), std::move(child));
        return it.second ? dynamic_cast<T*>((*it.first).second.get()) : nullptr;
    }
};