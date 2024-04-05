#include <argsParser.h>
#include <iostream>

using namespace std;

namespace BNet
{
    ArgsParser::ArgsParser(int argc, char** argv) noexcept {
        m_argc = argc;
        m_argv = argv;
        parse();
    }
    void ArgsParser::parseArgument(const std::string arg) noexcept {
        //Foreach without path to .exe
        for (size_t x = 0; x < m_argc; x++) {
            std::string curArg = m_argv[x]; // char* -> string
            auto findResult = curArg.find(arg);
            if (findResult != string::npos) {
                cout << "found instance" << endl;
                string value = arg.substr(findResult + arg.size());
                if (value.find('"') != string::npos) {
                    value = value.substr(value.find('"') + 1, value.find('"', 1) - 1); // "value" -> value
                }
                m_keys[arg] = value;
            }
        }
    }
    void ArgsParser::parse() noexcept {
        bool wasProblem = false;
        for (auto x : m_keys) {
            parseArgument(x.first);
            if (m_keys[x.second].empty()) {
                cout << "missed \"" << x.first << "\"" << endl;
                wasProblem = true;
            }
        }
        if (wasProblem)
            exit(-1);
    }
    string ArgsParser::getCMakePath() noexcept {
        return m_keys["-cmake"];
    }
    string ArgsParser::getCMakeListsPath() noexcept {
        return m_keys["-cmakeLists"];
    }
}