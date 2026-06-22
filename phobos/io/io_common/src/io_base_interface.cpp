#include "io_base_interface.hpp"
#include <ranges>

namespace Phobos::Io {

IoBaseInterface::IoBaseInterface(
        const std::string &name,
        const IoConfiguration &config,
        Phobos::Window::Window &window)
    : Phobos::EngineComponent{name}, configuration{config}, windowComponent{window} {
}

void IoBaseInterface::initialize() {
    // Base implementation - can be overridden in subclasses
}

Phobos::Io::Device::DeviceBaseInterface* IoBaseInterface::getDevice(IdType deviceId)
{
    auto it = devicesMap.find(deviceId);
    if (it == devicesMap.end())
        return nullptr;
    return it->second.get();
}

std::list<IdType> IoBaseInterface::getDeviceIds()
{
    return devicesMap | std::views::keys | std::ranges::to<std::list>();
}

} // namespace Phobos::Io
