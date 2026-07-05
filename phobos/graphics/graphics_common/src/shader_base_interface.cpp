#include "shader_base_interface.hpp"

using namespace Phobos;

Phobos::ShaderBaseInterface::ShaderBaseInterface(const std::string_view shaderName, IdType shaderId) : name{shaderName}, id{shaderId}
{
}

bool ShaderBaseInterface::operator<(const ShaderBaseInterface &other) const
{
    return id < other.id;
}

bool ShaderBaseInterface::operator==(const ShaderBaseInterface &other) const
{
    return id == id;
}

IdType Phobos::ShaderBaseInterface::getShaderId() const
{
    return id;
}

std::string Phobos::ShaderBaseInterface::getShaderName() const
{
    return name;
}
