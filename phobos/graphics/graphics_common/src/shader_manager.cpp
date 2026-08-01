#include "shader_manager.hpp"
#include <fstream>

using namespace Phobos;

inline std::vector<ShaderSource> Phobos::ShaderManager::getSourceFromFiles(std::vector<ShaderSourceFromFile> sources)
{
    std::vector<ShaderSource> result(sources.size());
    for (const auto &[type, sourcePath] : sources) {
        std::ifstream fileHandler{sourcePath, std::ios::in};
        if (!fileHandler.is_open())
            return {};
        std::stringstream ss;
        ss << fileHandler.rdbuf();
        result.emplace_back(type, ss.str());
    }
    return result;
}

bool Phobos::ShaderManager::deleteShader(const IdType)
{
    return false;
}

IdType Phobos::ShaderManager::createShader(std::vector<ShaderSource> sources)
{
    return IdType();
}

ShaderBaseInterface *Phobos::ShaderManager::getShader(IdType id)
{
    return nullptr;
}

IdType Phobos::ShaderManager::getShaderByname(std::string_view name) const
{
    return IdType();
}

std::vector<IdType> Phobos::ShaderManager::getAllIds() const
{
    return std::vector<IdType>();
}
