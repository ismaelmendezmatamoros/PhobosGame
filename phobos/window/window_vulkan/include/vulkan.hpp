#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Phobos {
namespace Window {
namespace Vulkan {

class VulkanContext {
public:
    VulkanContext();
    ~VulkanContext();

    bool initialize(GLFWwindow* window);
    void cleanup();
};

} // namespace Vulkan
} // namespace Window
} // namespace Phobos
