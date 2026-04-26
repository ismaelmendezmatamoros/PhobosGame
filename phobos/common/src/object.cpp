
#include "phobos/common/object.hpp"

using namespace Phobos;

const std::map<IdType, Object*> &Object::getObjectsRegistry() {
    return objectsRegistry;
}

Object::Object(std::shared_ptr<Object> parent) : parent{parent} {
    addToRegistry(this);
}

Object::Object(const Object &other) : PhobosClass{other}, parent{other.parent}  {
    addToRegistry(this);

}

Object::Object(Object &&other) : PhobosClass{std::move(other)}, parent{std::move(other.parent)} {
    addToRegistry(this);
    other.parent.reset();
}

Object& Object::operator=(const Object &other) {
    PhobosClass::operator=(other);
    parent = other.parent;
    addToRegistry(this);
    return *this;
}

Object& Object::operator=(Object &&other) {
    parent = other.parent = std::move(other.parent);
    PhobosClass::operator=(std::move(other));
    addToRegistry(this);
    other.parent.reset();
    return *this;
}

void Object::addToRegistry(Object *object) {
    std::shared_lock<std::shared_mutex> sl;
    objectsRegistry[object->getId()] = object;
}

bool Object::deleteChild(IdType childId) {
    std::unique_lock<std::shared_mutex> ul;
    return children.erase(childId) > 0;
}

void Object::addChild(std::shared_ptr<Object> child) {
    if (child == nullptr) {
        return;
    }
    std::unique_lock<std::shared_mutex> ul;
    children.insert_or_assign(child->getId(), child);
}

std::size_t Object::getChildrenCount() const {
    std::shared_lock<std::shared_mutex> sl;
    return children.size();
}

std::shared_ptr<Object> Object::getChild(IdType childId) const {
    std::shared_lock<std::shared_mutex> sl;
    return children.at(childId);
}

auto Object::getChildren() {
    std::shared_lock<std::shared_mutex> sl;
    return children | std::views::values;
}

auto Object::getChildrenIds() {
    std::shared_lock<std::shared_mutex> sl;
    return children | std::views::keys;
}


void Object::removeFromRegistry(Object *object) {
    std::unique_lock<std::shared_mutex> ul;
    objectsRegistry.erase(object->getId());
}