#pragma once

#include <string>
#include <cstdint>

#include "phobos/common/cpp_defs.hpp"

namespace Phobos::Common::Definitions {
    
    using IdType = std::uint64_t;
    static inline constexpr IdType invalidId{0};

    struct LogMessage {

        enum class SeverityLevel {
            DEBUG,
            INFO,
            WARNING,
            ERROR
        };

        IdType id;
        std::string header;
        std::string message;
        SeverityLevel severity;
    };
};