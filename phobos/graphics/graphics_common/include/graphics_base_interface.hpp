#pragma once

#include "common.hpp"
#include "engine_component.hpp"

namespace Phobos::Graphics {
class GraphicsBaseInterface :  public EngineComponent {
    public:
    GraphicsBaseInterface();
    virtual ~GraphicsBaseInterface() = default;

    //void execute() override;
    //void initialize() override;
    protected:
    static inline constexpr std::string graphicsNameStr{"Graphics"};
    
};

}