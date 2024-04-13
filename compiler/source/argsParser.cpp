#include <argsParser.h>
#include <corecrt_terminate.h>
#include <iostream>
#include <boost/program_options.hpp>

using namespace std;

namespace BNet
{
    ArgsParser::ArgsParser(int argc, char** argv) noexcept
        : m_desc("Allowed options") {
        m_desc.add_options()
        ("help", "produce help message")
        ("cmake", po::value<string>(&m_cmakePath)->default_value("base/cmake/bin/cmake.exe"), "set path to cmake.exe")
        ("cmakeLists", po::value<string>(&m_cmakeListsPath), "path to CMakeLists.txt")
        ("cmakeArgs", po::value<vector<string>>(&m_cmakeArgs)->multitoken(), "arguments to cmake");
        po::store(po::parse_command_line(argc, argv, m_desc), m_vm);
        po::notify(m_vm);

        if (m_vm.count("help")) {
            cout << m_desc << endl;
            std::exit(0);
        }
        if (!m_vm.count("cmakeLists")) {
            cout << "cmakeLists is not set" << endl;
            exit(0);
        }
    }
    vector<string> ArgsParser::getCMakeArgs() noexcept {
        return m_cmakeArgs;
    }
    string ArgsParser::getCMakePath() noexcept { 
        return m_cmakePath;
    }
    string ArgsParser::getCMakeListsPath() noexcept {
        return m_cmakeListsPath;
    }
}