#pragma once

#include "shader_stage_base_interface.hpp"
#include <map>
#include <memory>

namespace Phobos {

    class ShaderBaseInterface {
        public:
        //ShaderBaseInterface() = default;
        ShaderBaseInterface(const std::string_view shaderName, IdType id);
        virtual ~ShaderBaseInterface() = default;
        //void setStage()
        bool operator<(const ShaderBaseInterface &other) const;
        bool operator==(const ShaderBaseInterface &other) const;
        IdType getShaderId() const;
        std::string getShaderName() const;

        protected:
        std::map<ShaderStageType, std::unique_ptr<ShaderStageBaseInterface>> stages;
        std::string name;
        IdType id;
    };
}