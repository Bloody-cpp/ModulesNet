#include <argsParser.h>
#include <iostream>
#include <boost/program_options.hpp>
#include <exception>
#include <filesValidator.h>
#include <stdexcept>

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
            cout << exp.what() << endl;
            exit(0);
        }
        handleCommands();
        handleFiles();
    }
    void ArgsParser::handleFiles() {
        bool wasProblem = false;
        if (!validate(m_filesPaths, "--mnetFiles"))
            wasProblem = true;

        if (!validate(m_modulesPaths, "--modules"))
            wasProblem = true;

        if (!compareFilename(m_cmakeListsPath, "CMakeLists.txt") || !validate(m_cmakeListsPath)) {
            cout << "[--cmakeLists] " + m_cmakeListsPath + " is not exists" << endl;
            wasProblem = true;
        }

        if (wasProblem)
             throw runtime_error("incorrect path");
    }
    void ArgsParser::handleCommands() noexcept {
        if (m_vm.count("help")) {
            cout << m_desc << endl;
            exit(0);
        }
        bool wasProblem = false;
        if (!m_vm.count("cmakeLists")) {
            cout << "Argument cmakeLists required by compiler, please create someone" << endl;
            wasProblem = true;
        }
        if (!m_vm.count("mnetFiles")) {
            cout << "Argument mnetFiles required by compiler, please create someone";
            wasProblem = true;
        }
        if (wasProblem)
            exit(0);
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