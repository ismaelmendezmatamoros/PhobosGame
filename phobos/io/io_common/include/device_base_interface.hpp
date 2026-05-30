#pragma once

#include "io_definitions.hpp"
#include "common.hpp"

#include <string>
#include <vector>
#include <map>

namespace Phobos::Io::Device {
    
    class DeviceBaseInterface : public PhobosClass {
        public:
        DeviceBaseInterface(
                DeviceType _type,
                const std::string &deviceName) 
                    : type{_type}
                    , name{deviceName} {

        logMessage("Created");
        }
        virtual ~DeviceBaseInterface() = default;
        std::string formatHeader() const override { return name;}

        DeviceType getType() const {return type;}
        void setType(DeviceType _type) {type = _type;}

        std::string getName() const {return name;}
        void setName(std::string _name) {name = _name;}

        virtual std::map<KeyBoardKeyType, KeyStatus> readStatus(const std::vector<KeyBoardKeyType> &filter = {}) = 0;

        protected:

        std::string name;
        DeviceType type;
    };
};