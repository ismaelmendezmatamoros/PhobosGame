#pragma once

#include <string>
#include <string_view>
#include <format>
#include <iostream>
#include <mutex>
#include <queue>

#include "phobos/common/log_message.hpp"


namespace Phobos {

class Logger {
    public:

    static void logMessage(const LogMessage &message);
    static void logMessage(std::string_view message, const LogMessage::SeverityLevel severity = LogMessage::SeverityLevel::INFO);

    private:
    static std::string getCurrentTimeToStr();
    static void handleMessage(std::string_view message, const LogMessage::SeverityLevel severity);
    
    static inline std::mutex logMutex;
};
};
