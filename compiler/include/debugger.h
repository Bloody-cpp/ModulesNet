#ifndef COMPILER_INCLUDE_DEBUGGER
#define COMPILER_INCLUDE_DEBUGGER

#include <iostream>
#include "../lang/include/debuggerSingleton.h"

namespace mnet {
    class CompilerDebugger : public IDebugger {
    public:
        void echo(MsgType type, std::string msg, DebugInfo info) override {
            switch (type) {
            case mnet::MsgType::info:
                std::cout << "[INFO] " << info.m_file->m_path << " " << msg << std::endl;
                break;
            case mnet::MsgType::warning:
                std::cout << "[WARNING] " << info.m_file->m_path << " " << msg << std::endl;
                break;
            case mnet::MsgType::error:
                std::cout << "[ERROR] " << info.m_file->m_path << " <" << info.m_component << "> " << msg << std::endl;
                exit(100);
                break;
            }
        }
        void stEcho(
            MsgType type, 
            std::string msg, 
            std::string component, 
            std::string filePath
        ) override {
            switch (type) {
            case mnet::MsgType::info:
                std::cout << "[INFO] " << filePath << " " << msg << std::endl;
                break;
            case mnet::MsgType::warning:
                std::cout << "[WARNING] " << filePath << " " << msg << std::endl;
                break;
            case mnet::MsgType::error:
                std::cout << "[ERROR] " << filePath << " <" << component << "> " << msg << std::endl;
                exit(100);
                break;
        }
        }
    };
}

#endif /* COMPILER_INCLUDE_DEBUGGER */
