#ifndef COMPILER_LANG_INCLUDE_DEBUGGERSINGLETON
#define COMPILER_LANG_INCLUDE_DEBUGGERSINGLETON

#include <iostream>
#include "../include/include.h"

namespace mnet {
    struct DebugInfo {
        file_t* m_file;
        std::string m_component;
    };

    enum MsgType : char {
        info = 0,
        warning = 1,
        error = 2
    };
    
    struct ThrowInfo {
        DebugInfo info;
        MsgType type;
        std::string msg;
    };
    
    class IDebugger {
    public:
        virtual void echo(MsgType type, std::string msg, DebugInfo info) = 0;
    };

    class DebuggerSingleton {
        DebugInfo m_debugInfo;
        inline static IDebugger* m_debugger = nullptr;
    public:
        static void initializeDebugger(IDebugger* debugger) noexcept;
    protected:
        void setDebugInfo(const DebugInfo info) noexcept;
        void echo(std::string msg, MsgType type = info) noexcept;
    };
}

#endif /* COMPILER_LANG_INCLUDE_DEBUGGERSINGLETON */
