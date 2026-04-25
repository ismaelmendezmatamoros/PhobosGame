#pragma once

#include <string>

namespace phobos::io {

class FileSystem {
public:
    FileSystem();
    ~FileSystem() = default;
    
    bool fileExists(const std::string& path) const;
    std::string readFile(const std::string& path) const;
    bool writeFile(const std::string& path, const std::string& content) const;
    
private:
};

} // namespace phobos::io
