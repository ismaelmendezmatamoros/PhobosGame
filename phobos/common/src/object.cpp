
#include "object.hpp"

using namespace Phobos;

const std::map<IdType, Object*> &Object::getObjectsRegistry() {
    return objectsRegistry;
}

Object::Object(Object *parentObject)
        :parent{parentObject} {
    addToRegistry(this);
}

Object::Object(const Object &other)
        :PhobosClass{other}
        ,parent{other.parent}  {
    addToRegistry(this);
}

Object::Object(Object &&other)
        :PhobosClass{std::move(other)}
        ,parent{std::move(other.parent)} {
    addToRegistry(this);
    other.parent = nullptr;
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
    other.parent = nullptr;
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

void Object::addChild(Object *child) {
    if (child == nullptr)
        return;
    auto key = child->getId();
    auto childParent = child->parent;
    std::unique_lock<std::shared_mutex> childrenUl(childrenMutex);
    if (childParent == nullptr) {
        children.insert_or_assign(key , std::unique_ptr<Phobos::Object>(child));
        childParent = this;
        return;
    }
    std::unique_lock<std::shared_mutex> parentChildrenUl(childParent->childrenMutex);
    auto node = childParent->children.extract(key);
    children.insert(std::move(node));
    child->parent = this;
}

std::size_t Object::getChildrenCount() const {
    std::shared_lock<std::shared_mutex> sl;
    return children.size();
}

Object* Object::getChild(IdType childId) const {
    std::shared_lock<std::shared_mutex> sl;
    return children.at(childId).get();
}

std::list<Object*> Object::getChildren() const {
    std::shared_lock<std::shared_mutex> sl;
    auto getPointer = [](const std::unique_ptr<Object> &ptr) {return ptr.get();};
    auto values_view = children | std::views::values | std::views::transform(getPointer);
    return std::ranges::to<std::list<Object*>>(values_view);
}

std::list<IdType> Object::getChildrenIds() const {
    std::shared_lock<std::shared_mutex> sl;
    auto keys_range = children | std::views::keys;
    return std::ranges::to<std::list<IdType>>(keys_range);
}

void Object::removeFromRegistry(IdType ObjectId) {
    std::unique_lock<std::shared_mutex> ul;
    objectsRegistry.erase(ObjectId);
}