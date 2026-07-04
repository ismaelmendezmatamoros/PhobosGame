#include "shader_stage_opengl.hpp"

using namespace Phobos::Graphics::OpenGL;

ShaderStageOpenGl::ShaderStageOpenGl(const ShaderStageType type, const std::string_view code, const std::string shaderName)
        : ShaderStageBaseInterface {type, code, shaderName} {

}

void ShaderStageOpenGl::addParameterImp(int layout, std::span<const std::byte> data, std::size_t size)
{
    logMessage("Added to layout");
}

/*std::optional<std::string> ShaderStageOpenGl::compile()
{
    logMessage("compiled");
    return std::optional<std::string>();
}
*/
