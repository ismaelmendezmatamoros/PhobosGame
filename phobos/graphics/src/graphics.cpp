#include "phobos/graphics/graphics.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace phobos::graphics {

Renderer::Renderer() 
    : projectionMatrix(1.0f), viewMatrix(1.0f) {
}

void Renderer::initialize() {
    // Inicializar matrices de proyección
    projectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

void Renderer::shutdown() {
    // Limpiar recursos
}

void Renderer::render() {
    // Renderizar frame
}

glm::mat4 Renderer::getProjectionMatrix() const {
    return projectionMatrix;
}

glm::mat4 Renderer::getViewMatrix() const {
    return viewMatrix;
}

} // namespace phobos::graphics
