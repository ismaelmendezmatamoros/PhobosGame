#pragma once

#include "shader_stage_base_interface.hpp"

namespace Phobos::Graphics::OpenGL {
    class ShaderStageOpenGl : public ShaderStageBaseInterface {
        public:
        ShaderStageOpenGl(const ShaderStageType type, const std::string_view code, const std::string shaderName = "");
        ~ShaderStageOpenGl() = default;

        protected:
        void addParameterImp(int layout, std::span<const std::byte> data) override;

        std::optional<std::string> compile() override; 
    };
}