#pragma once

#include "phobos_class.hpp"

#include <string>
#include <string_view>
#include <optional>
#include <span>
#include <concepts>

namespace Phobos {
    enum class ShaderStageType {
        VertexShader = 0,
        Geometric,
        Fragment,
        Compute,
        TessControl,
        TessEvaluation,
        Count
    };

    static inline std::map<ShaderStageType, const std::string> ShaderStageNameMap {
        {ShaderStageType::VertexShader, "VertexShader"}, 
        {ShaderStageType::Geometric, "Geometric"}, 
        {ShaderStageType::Fragment, "Fragment"}, 
        {ShaderStageType::Compute, "Compute"}, 
        {ShaderStageType::TessControl, "TessControl"}, 
        {ShaderStageType::TessEvaluation, "TessEvaluation"}, 
        {ShaderStageType::Count, "Count"}
    };

    template<typename T>
    concept ContiguousRange = std::ranges::contiguous_range<T>;

    class ShaderStageBaseInterface : public PhobosClass {
        public:
        ShaderStageBaseInterface(const ShaderStageType type, const std::string_view code, const std::string shaderName = "");
        virtual ~ShaderStageBaseInterface() = default;

        ShaderStageType getType() const;
        const std::string_view getCode() const;
        const std::string_view getname() const;
        
        virtual void addParameterImp(int layout, std::span<const std::byte> data) = 0;
        std::string formatHeader() const override;

        template <typename T>
            requires (!ContiguousRange<T>)
        void addParameter(int layout, const T &data) { 
            std::span<const T> dataSpan{&data, 1};
            logMessage("singleee");
            addParameterImp(layout, std::as_bytes(dataSpan));
        }

        template <ContiguousRange T>
        void addParameter(int layout, const T &data) { 
            std::span<const std::ranges::range_value_t<T>> dataSpan{data};
            addParameterImp(layout, std::as_bytes(dataSpan));
        }

        virtual std::optional<std::string> compile() = 0;        

        protected:
        ShaderStageType stageType;
        std::string codeText;
        bool compiled;
        std::string name;
    };
}