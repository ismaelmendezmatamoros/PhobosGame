

#include "phobos/common/logger.hpp"
#include "phobos/common/definitions.hpp"
#include <iostream>
#include <format>
#include <chrono>
#include <mutex>


using namespace Phobos::Common;

void Phobos::Logger::logMessage(const LogMessage &message) {

    static constexpr std::string_view noHeaderFormat{"[{}][ID:{}]:{}"};
    static constexpr std::string_view headerFormat{"[{}][ID:{}]:{}|{}"};

    auto time_stamp = getCurrentTimeToStr();

    auto formatted_text = message.header.empty()
            ? std::format(noHeaderFormat, time_stamp, message.id, message.message)
            : std::format(headerFormat, time_stamp, message.id, message.header, message.message);

    handleMessage(formatted_text, message.severity);
}

void Phobos::Logger::handleMessage(const std::string_view message, const LogMessage::SeverityLevel severity) {
    static std::mutex loggerMutex;
    std::lock_guard<std::mutex> loggerMutexLg{loggerMutex};

    switch(severity) {
        case LogMessage::SeverityLevel::ERROR: {
            std::cerr << message << std::endl;
            break;
        }
        default: {
            std::cout << message << std::endl;
        }
    }   
}

void Phobos::Logger::logMessage(const std::string_view message, const LogMessage::SeverityLevel severity) {
    auto time_stamp = getCurrentTimeToStr();
    handleMessage(message, severity);
}

std::string Phobos::Logger::getCurrentTimeToStr() {
    using namespace std::chrono;

    const auto now = system_clock::now();
    const auto ms = duration_cast<milliseconds>(
        now.time_since_epoch()) % 1000;

    return std::format("{:%H:%M:%S}.{:03}",
                       floor<seconds>(now),
                       ms.count());
}