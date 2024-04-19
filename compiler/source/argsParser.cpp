#include "../include/argsParser.h"
#include "../include/filesManager.h"
#include "../lang/include/debuggerSingleton.h"
#include <iostream>
#include <boost/program_options.hpp>
#include <exception>

using namespace std;

namespace mnet
{
    ArgsParser::ArgsParser(int argc, char** argv)
        : m_desc("Allowed options") {
        m_desc.add_options()
        ("help,h", "produce help message")
        ("cmake,c", po::value<string>(&m_cmakePath)->default_value("base/cmake/bin/cmake.exe"), "Set path to cmake.exe")
        ("cmakeLists,l", po::value<string>(&m_cmakeListsPath), "Path to CMakeLists.txt")
        ("cmakeArgs,a", po::value<vector<string>>(&m_cmakeArgs)->multitoken(), "Arguments to cmake")
        ("mnetFiles,f", po::value<vector<string>>(&m_filesPaths)->multitoken(), "Files to compile")
        ("modules,m", po::value<vector<string>>(&m_modulesPaths)->multitoken(), "Path to modules which be link");

        try {
            po::store(po::parse_command_line(argc, argv, m_desc), m_vm);
            po::notify(m_vm);
        }
        catch(exception& exp) {
            DebuggerSingleton::echo(exp.what(), error, "ArgsParser, boost exception", "");
        }
        handleCommands();
        handleFiles();
    }
    void ArgsParser::handleFiles() {
        validate(m_filesPaths, "--mnetFiles");
        validate(m_modulesPaths, "--modules");

        if (!compareFilename(m_cmakeListsPath, "CMakeLists.txt") || !validate(m_cmakeListsPath))
            DebuggerSingleton::echo("is not exists", error, "--cmakeLists", m_cmakeListsPath);
    }
    void ArgsParser::handleCommands() noexcept {
        if (m_vm.count("help")) {
            cout << m_desc << endl;
            exit(0);
        }
        if (!m_vm.count("cmakeLists"))
            DebuggerSingleton::echo("Argument cmakeLists requierd by compiler", error, "ArgsParser", "");
        if (!m_vm.count("mnetFiles"))
            DebuggerSingleton::echo("Argument mnetFiles requierd by compiler", error, "ArgsParser", "");
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
    vector<string> ArgsParser::getModulesPath() noexcept {
        return m_modulesPaths;
    }
    vector<string> ArgsParser::getFilesPaths() noexcept {
        return m_filesPaths;
    }
}