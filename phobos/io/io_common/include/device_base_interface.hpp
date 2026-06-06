#pragma once

#include "io_definitions.hpp"
#include "key_mapper_base_interface.hpp"
#include "common.hpp"

#include <string>
#include <vector>
#include <map>
#include <concepts>

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

        template<std::derived_from<KeyMapperBaseInterface> T, typename ...Args>
        void emplaceKeyMapper(Args&& ...args) {
            auto mapper = std::make_unique<T>(std::forward<Args>(args)...);
            mappers.push_back(std::move(mapper));
        }

        virtual DeviceKeysStatus readStatus(const std::vector<KeyBoardKeyType> &filter = {}) = 0;

        void callMappers() {
            auto status = readStatus();
            for(auto &mapper: mappers) {
                mapper->mapKeys(status);
            }
        }

        protected:
        std::string name;
        DeviceType type;
        std::list<std::unique_ptr<KeyMapperBaseInterface>> mappers;
    };
};