#pragma once

#include <string>
#include <filesystem>

namespace phobos::io {

class FileSystem {
public:
    FileSystem();
    ~FileSystem() = default;
    
    bool fileExists(const std::filesystem::path & path) const;
    std::string readFile(const std::filesystem::path& path) const;
    bool writeFile(const std::filesystem::path& path, const std::string& content) const;
    
private:
};

}
