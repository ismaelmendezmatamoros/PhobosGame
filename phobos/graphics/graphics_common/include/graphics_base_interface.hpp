#pragma once

#include "common.hpp"
#include "window_base_interface.hpp"
#include "gpu_memory_manager_base_interface.hpp"

namespace Phobos::Graphics {
class GraphicsBaseInterface :  public EngineComponent {
    public:
    GraphicsBaseInterface();
    virtual ~GraphicsBaseInterface() = default;

    //void execute() override;
    //void initialize() override;
    virtual GPUMemoryManagerBaseInterface* getGPUMemoryManager() = 0;

    protected:
    static inline constexpr std::string graphicsNameStr{"Graphics"};
    Window::WindowBaseInterface *window;
    

    
};

}