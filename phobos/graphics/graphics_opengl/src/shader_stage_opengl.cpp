#include "shader_stage_opengl.hpp"
#include <sstream>
using namespace Phobos::Graphics::OpenGL;

ShaderStageOpenGl::ShaderStageOpenGl(const ShaderStageType type, const std::string_view code)
        : ShaderStageBaseInterface {type, code} {

}

void ShaderStageOpenGl::addParameterImp(int layout, std::span<const std::byte> data)
{
}

std::optional<std::string> ShaderStageOpenGl::compile()
{
    return std::optional<std::string>();
}

