#pragma once

#include <glm/glm.hpp>
#include "graphics_base_interface.hpp"
#include "shader_stage_opengl.hpp"
#include "gpu_buffer_opengl.hpp"
#include "gpu_memory_manager_opengl.hpp"

namespace Phobos::Graphics::OpenGL {

class GraphicsOpenGL : public Phobos::Graphics::GraphicsBaseInterface {
public:
    GraphicsOpenGL();
    ~GraphicsOpenGL() = default;

    void initialize() override;
    void execute() override;

    GPUMemoryManagerBaseInterface* getGPUMemoryManager() override;

    //void initialize();
    //void shutdown();
    //void render();

    //glm::mat4 getProjectionMatrix() const;
    //glm::mat4 getViewMatrix() const;

private:
    GPUMemoryManagerOpenGL gpuMemoryManager;
    //glm::mat4 projectionMatrix;
    //glm::mat4 viewMatrix;
};

} // namespace Phobos::Graphics::OpenGL
