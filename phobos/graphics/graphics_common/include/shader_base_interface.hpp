#pragma once

#include "shader_stage_base_interface.hpp"
#include <map>
#include <memory>

namespace Phobos {

    class ShaderBaseInterface {
        public:
        //ShaderBaseInterface() = default;
        virtual ~ShaderBaseInterface() = default;
        protected:
        std::map<ShaderStageType, std::unique_ptr<ShaderStageBaseInterface>> stages;
    };
}