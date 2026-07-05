#include "shader_stage_opengl.hpp"
#include <sstream>
using namespace Phobos::Graphics::OpenGL;

ShaderStageOpenGl::ShaderStageOpenGl(const ShaderStageType type, const std::string_view code, const std::string shaderName)
        : ShaderStageBaseInterface {type, code, shaderName} {

}

void ShaderStageOpenGl::addParameterImp(int layout, std::span<const std::byte> data)
{
    std::stringstream ss;
    ss << "Added to layout " << data.size_bytes();
    for (const auto &l: data)
        ss << " " << std::to_integer<int>(l);   
    logMessage(ss.str());

}

std::optional<std::string> ShaderStageOpenGl::compile()
{
    logMessage("compiled");
    return std::optional<std::string>();
}

