#pragma once

#include <string>
#include <string_view>
#include <format>
#include <iostream>
#include <mutex>
#include <queue>

#include "log_message.hpp"


namespace Phobos {

class Logger {
    public:

    static void logMessage(const LogMessage &message);
    static void logMessage(const std::string_view message, const LogMessage::SeverityLevel severity = LogMessage::SeverityLevel::INFO);

    private:
    static std::string getCurrentTimeToStr();
    static void handleMessage(const std::string_view message, const LogMessage::SeverityLevel severity);

    static inline std::mutex logMutex;
};
};
