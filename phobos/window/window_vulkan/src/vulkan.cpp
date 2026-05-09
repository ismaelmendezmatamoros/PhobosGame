#include "vulkan.hpp"

namespace Phobos {
namespace Window {
namespace Vulkan {

VulkanContext::VulkanContext() {
}

VulkanContext::~VulkanContext() {
}

bool VulkanContext::initialize(GLFWwindow* window) {
    // Placeholder: create Vulkan instance / surface here.
    return true;
}

void VulkanContext::cleanup() {
}

} // namespace Vulkan
} // namespace Window
} // namespace Phobos
