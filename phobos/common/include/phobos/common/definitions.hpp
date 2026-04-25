#pragma once

#include <string>

namespace Phobos::Common::Definitions {
    using IdType = unsigned int;
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