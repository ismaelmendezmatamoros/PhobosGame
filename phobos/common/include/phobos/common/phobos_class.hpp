 #pragma once

#include <atomic>
#include <string_view>
#include "phobos/common/definitions.hpp"
#include "phobos/common/logger.hpp"



namespace Phobos {

class PhobosClass {
    
    static inline constexpr IdType invalidId{0};
    static inline std::atomic<IdType> idCounter{invalidId + 1};

    public:
    PhobosClass();
    PhobosClass(const PhobosClass &other);
    PhobosClass(PhobosClass &&other);
    PhobosClass &operator=(const PhobosClass &other);
    PhobosClass &operator=(PhobosClass &&other);

    virtual std::string formatHeader() const;
    void logMessage(const std::string_view message, const LogMessage::SeverityLevel severity = LogMessage::SeverityLevel::INFO) const;
    


    IdType getId() const;

    virtual ~PhobosClass() = default;

    private:
    LogMessage generateLogMessage(const std::string_view message, const LogMessage::SeverityLevel severity) const;
    IdType id;
};
};