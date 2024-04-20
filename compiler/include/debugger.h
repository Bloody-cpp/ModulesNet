#ifndef COMPILER_INCLUDE_DEBUGGER
#define COMPILER_INCLUDE_DEBUGGER

#include <iostream>
#include "../lang/include/debuggerSingleton.h"

namespace mnet {
    class CompilerDebugger : public IDebugger {
        void positionPrint(int line, int index) {
            if (line) {
                std::cout << " " << line;
                if (index)
                    std::cout << " " << index << " ";
            }
        }
    public:
        void echo(MsgType type, std::string msg, DebugInfo info, int line, int index) override {
            switch (type) {
            case mnet::MsgType::info:
                std::cout << "[INFO] " << info.m_file->m_path;
                positionPrint(line, index);
                std::cout << " " << msg << std::endl;
                break;
            case mnet::MsgType::warning:
                std::cout << "[WARNING] " << info.m_file->m_path;
                positionPrint(line, index);
                std::cout << " " << msg << std::endl;
                break;
            case mnet::MsgType::error:
                std::cout << "[ERROR] " << info.m_file->m_path;
                positionPrint(line, index);
                std::cout << " <" << info.m_component << "> " << msg << std::endl;
                exit(100);
                break;
            }
        }
        void stEcho(
            MsgType type, 
            std::string msg, 
            std::string component, 
            std::string filePath,
            int line,
            int index
        ) override {
            switch (type) {
            case mnet::MsgType::info:
                std::cout << "[INFO] " << filePath;
                positionPrint(line, index);
                std::cout << msg << std::endl;
                break;
            case mnet::MsgType::warning:
                std::cout << "[WARNING] " << filePath;
                positionPrint(line, index);
                std::cout << msg << std::endl;
                break;
            case mnet::MsgType::error:
                std::cout << "[ERROR] " << filePath;
                positionPrint(line, index);
                std::cout << " <" << component << "> " << msg << std::endl;
                exit(100);
                break;
        }
        }
    };
}

#endif /* COMPILER_INCLUDE_DEBUGGER */
