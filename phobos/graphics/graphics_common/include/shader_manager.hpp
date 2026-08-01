#pragma once

#include "shader_base_interface.hpp"
#include <map>
#include <memory>
#include <string_view>
#include <vector>
#include <filesystem>

namespace Phobos {
    struct ShaderSource {
        ShaderStageType type;
        std::string code;
    };

    struct ShaderSourceFromFile {
        ShaderStageType type;
        std::filesystem::path filePath;
    };

    class ShaderManager {
        public:
        static inline std::vector<ShaderSource> getSourceFromFiles(std::vector<ShaderSourceFromFile> sources);

        bool deleteShader(const IdType);
        IdType createShader(std::vector<ShaderSource> sources);
        
        ShaderBaseInterface* getShader(IdType id);
        IdType getShaderByname(std::string_view name) const;
        std::vector<IdType> getAllIds() const;
        
        private:
        std::map<IdType, std::unique_ptr<ShaderBaseInterface>> shadersMap;
    };
};