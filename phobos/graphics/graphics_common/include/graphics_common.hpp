#pragma once

#include <glm/glm.hpp>

namespace Phobos::Graphics {

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

} // namespace Phobos::Graphics
