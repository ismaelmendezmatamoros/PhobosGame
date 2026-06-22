#pragma once

#include "definitions.hpp"
#include "phobos_class.hpp"

#include <string>
#include <string_view>
#include <format>

namespace Phobos {

    class EngineComponent: public PhobosClass {
        
        public:
        EngineComponent(const std::string name)
                : PhobosClass{}
                , componentName{name} {
            logMessage(std::format("Created"), LogMessage::SeverityLevel::INFO);
        }

        virtual ~EngineComponent() {
            logMessage(std::format("Finalizing"), LogMessage::SeverityLevel::INFO);
        }

        std::string formatHeader() const override { return componentName;}
        virtual void initialize() = 0;
        virtual void execute() = 0;

        protected:
        std::string componentName;
    };
}