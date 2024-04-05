#ifndef COMPILER_INCLUDE_ARGSPARSER
#define COMPILER_INCLUDE_ARGSPARSER

#include <string>
#include <map>
#include <unordered_map>

#define KEY_CMAKE "-cmake="
#define KEY_COMPILER "-compiler="
#define KEY_CMAKELISTS "-cmakeLists="

namespace BNet
{
    class ArgsParser
    {
        int m_argc;
        char** m_argv;
        std::unordered_map<std::string, std::string> m_keys = {
            {"-cmake", "base/cmake/bin/cmake.exe"},
            {"-cmakeLists", ""}
        };
    public:
        ArgsParser(int argc, char** argv) noexcept;
        ~ArgsParser() noexcept = default;

        void parse() noexcept;
        void parseArgument(const std::string arg) noexcept;
        std::string getCMakePath() noexcept;
        std::string getCMakeListsPath() noexcept;
    };
}

#endif /* COMPILER_INCLUDE_ARGSPARSER */
