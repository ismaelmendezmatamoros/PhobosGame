#include "graphics_opengl.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Phobos::Graphics::OpenGL {

GraphicsOpenGL::GraphicsOpenGL()
    //: projectionMatrix(1.0f), viewMatrix(1.0f) {
{
}

void GraphicsOpenGL::initialize()
{
    logMessage("OpenGlGraphicsInitialized");
}

void GraphicsOpenGL::execute()
{
}

/*

void GraphicsOpenGL::shutdown() {
}

void GraphicsOpenGL::render() {
}

glm::mat4 GraphicsOpenGL::getProjectionMatrix() const {
    return projectionMatrix;
}

glm::mat4 GraphicsOpenGL::getViewMatrix() const {
    return viewMatrix;
}
*/

} // namespace Phobos::Graphics::OpenGL
