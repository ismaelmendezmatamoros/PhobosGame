#include "phobos/io/io.hpp"
#include <fstream>

namespace phobos::io {

FileSystem::FileSystem() = default;

bool FileSystem::fileExists(const std::string& path) const {
    std::ifstream file(path);
    return file.good();
}

std::string FileSystem::readFile(const std::string& path) const {
    std::ifstream file(path);
    std::string content((std::istreambuf_iterator<char>(file)), 
                        std::istreambuf_iterator<char>());
    return content;
}

bool FileSystem::writeFile(const std::string& path, const std::string& content) const {
    std::ofstream file(path);
    if (file.is_open()) {
        file << content;
        file.close();
        return true;
    }
    return false;
}

} // namespace phobos::io
