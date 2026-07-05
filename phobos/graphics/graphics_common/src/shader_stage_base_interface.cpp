#include "shader_stage_base_interface.hpp"

using namespace Phobos;

ShaderStageBaseInterface::ShaderStageBaseInterface(const ShaderStageType type, const std::string_view code)
    : stageType{type}
    , codeText{code}
    , compiled{false}
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

bool Phobos::ShaderStageBaseInterface::isLoaded() const
{
    return loaded;
}


