
#include "phobos/common/object.hpp"

using namespace Phobos;

const std::map<IdType, Object*> &Object::getObjectsRegistry() {
    return objectsRegistry;
}

Object::Object() {
    addToRegistry(this);
}

Object::Object(const Object &other) : PhobosClass{other} {
    addToRegistry(this);
}

Object::Object(Object &&other) : PhobosClass{std::move(other)} {
    addToRegistry(this);
}

Object& Object::operator=(const Object &other) {
    PhobosClass::operator=(other);
    addToRegistry(this);
    return *this;
}

Object& Object::operator=(Object &&other) {
    PhobosClass::operator=(std::move(other));
    addToRegistry(this);
    return *this;
}

void Object::addToRegistry(Object *object) {
    std::shared_lock<std::shared_mutex> sl;
    objectsRegistry[object->getId()] = object;
}

void Object::removeFromRegistry(Object *object) {
    std::unique_lock<std::shared_mutex> ul;
    objectsRegistry.erase(object->getId());
}