#pragma once

#include <glm/glm.hpp>
#include <string>

namespace phobos::graphics {

class Renderer {
public:
    Renderer();
    ~Renderer() = default;
    
    void initialize();
    void shutdown();
    void render();
    
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
    
private:
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
};

} // namespace phobos::graphics
