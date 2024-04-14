#ifndef COMPILER_INCLUDE_FILESVALIDATOR
#define COMPILER_INCLUDE_FILESVALIDATOR

#include <string>
#include <vector>
#include <filesystem>

namespace mnet {
    namespace fs = std::filesystem;

    bool validate(const std::vector<std::string> paths, std::string handle) noexcept;
    bool validate(const std::string path) noexcept;
    
    bool compareExtension(fs::path path, std::string extension) noexcept;
    bool compareFilename(fs::path path, std::string filename) noexcept;
}

#endif /* COMPILER_INCLUDE_FILESVALIDATOR */
