#pragma once

#include "phobos_class.hpp"

#include <string>
#include <string_view>
#include <optional>
#include <span>

namespace Phobos {
    enum class ShaderStageType {
        VertexShader = 0,
        Geometric,
        Fragment,
        Count
    };

    static inline std::map<ShaderStageType, const std::string> ShaderStageNameMap {
        {ShaderStageType::VertexShader, "VertexShader"}, 
        {ShaderStageType::Geometric, "Geometric"}, 
        {ShaderStageType::Fragment, "Fragment"}, 
        {ShaderStageType::Count, "Count"}
    };

    class ShaderStageBaseInterface : public PhobosClass {
        public:
        ShaderStageBaseInterface(const ShaderStageType type, const std::string_view code, const std::string shaderName = "");
        virtual ~ShaderStageBaseInterface() = default;

        ShaderStageType getType() const;
        const std::string_view getCode() const;
        const std::string_view getname() const;
        
        virtual void addParameterImp(int layout, std::span<const std::byte> data , std::size_t size) = 0;
        std::string formatHeader() const override;

        template <typename T>
        void addparameter(int layout, auto data) { 
            std::span<T> dataSpan{data};
            addParameterImp(layout, dataSpan.as_bytes(), dataSpan.size_bytes());
        }

        //virtual std::optional<std::string> compile() = 0;        

        protected:
        ShaderStageType stageType;
        std::string codeText;
        bool compiled;
        std::string name;
    };
}