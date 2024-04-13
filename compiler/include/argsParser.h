#ifndef COMPILER_INCLUDE_ARGSPARSER
#define COMPILER_INCLUDE_ARGSPARSER

#include <string>
#include <vector>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace BNet
{
    class ArgsParser
    {
        std::string m_cmakePath;
        std::string m_cmakeListsPath;
        std::vector<std::string> m_cmakeArgs;

        po::options_description m_desc;
        po::variables_map m_vm;
    public:
        ArgsParser(int argc, char** argv) noexcept;
        ~ArgsParser() noexcept = default;

        std::vector<std::string> getCMakeArgs() noexcept;
        std::string getCMakePath() noexcept;
        std::string getCMakeListsPath() noexcept;
    };
}

#endif /* COMPILER_INCLUDE_ARGSPARSER */
