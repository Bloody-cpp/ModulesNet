#ifndef COMPILER_INCLUDE_FILESMANAGER
#define COMPILER_INCLUDE_FILESMANAGER

#include <string>
#include <vector>
#include <filesystem>

namespace mnet {
    namespace fs = std::filesystem;

    void validate(const std::vector<std::string> paths, std::string handle) noexcept;
    bool validate(const std::string path) noexcept;
    
    bool compareExtension(fs::path path, std::string extension) noexcept;
    bool compareFilename(fs::path path, std::string filename) noexcept;

    std::string getFileName(fs::path path) noexcept;
}

#endif /* COMPILER_INCLUDE_FILESMANAGER */
