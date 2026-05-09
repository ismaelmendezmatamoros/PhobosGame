#pragma once

#include <string>
#include <cstdint>
#include <concepts>

#include "cpp_defs.hpp"

namespace Phobos {
    
    using IdType = std::uint64_t;
    static inline constexpr IdType invalidId{0};

    template<typename T>
    concept ValidKey = requires(const 
        T &a, const T &b) {
        {std::less<T>{}(a, b)} -> std::convertible_to<bool>;
    } && std::copy_constructible<T>;

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