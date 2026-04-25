#include "phobos/common/phobos_class.hpp"

using namespace Phobos::Common;

PhobosClass::PhobosClass() : id{idCounter++} {}

IdType PhobosClass::getId() const {
    return id;
}

PhobosClass::PhobosClass(const PhobosClass &other) : id{idCounter++} {}

PhobosClass::PhobosClass(PhobosClass &&other): id{other.id} {
    other.id = invalidId;
}

PhobosClass &PhobosClass::operator=(const PhobosClass &other) {
    id = idCounter++;
    return *this;
}

std::string PhobosClass::formatHeader() const {
    return "";
}

LogMessage PhobosClass::generateLogMessage(
        const std::string_view message,
        const LogMessage::SeverityLevel severity) const {
    LogMessage msg;
    msg.id = id;
    msg.severity = severity;
    msg.message = message;
    msg.header = formatHeader();
    return msg;
}

void PhobosClass::logMessage(
        const std::string_view message,
        const LogMessage::SeverityLevel severity) const {
        auto msg = generateLogMessage(message, severity);
        Phobos::Logger::logMessage(msg);
}

PhobosClass &PhobosClass::operator=(PhobosClass &&other) {
    id = other.id;
    other.id = invalidId;
    return *this;
}
