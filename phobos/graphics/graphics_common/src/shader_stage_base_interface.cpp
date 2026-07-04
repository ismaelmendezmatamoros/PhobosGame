#include "shader_stage_base_interface.hpp"

using namespace Phobos;

ShaderStageBaseInterface::ShaderStageBaseInterface(const ShaderStageType type, const std::string_view code, const std::string shaderName)
    : stageType{type}
    , codeText{code}
    , compiled{false}
    , name{shaderName.empty() ? "Shader " + ShaderStageNameMap[type] : shaderName }

{
}

ShaderStageType Phobos::ShaderStageBaseInterface::getType() const
{
    return stageType;
}

const std::string_view Phobos::ShaderStageBaseInterface::getCode() const
{
    return codeText;
}

const std::string_view Phobos::ShaderStageBaseInterface::getname() const
{
    return name;
}

std::string Phobos::ShaderStageBaseInterface::formatHeader() const
{
    return std::format("{} {}", name, ShaderStageNameMap[stageType]);
}
