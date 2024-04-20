#include "../include/debuggerSingleton.h"

using namespace mnet;
using namespace std;

void DebuggerSingleton::initializeDebugger(IDebugger *debugger) noexcept {
    m_debugger = debugger;
}

void DebuggerSingleton::setDebugInfo(const DebugInfo info) noexcept {
    m_debugInfo = info;
}

void DebuggerSingleton::echo(string msg, MsgType type, int line, int index) noexcept {
    m_debugger->echo(type, msg, m_debugInfo, line, index);
}

void DebuggerSingleton::echo(
    std::string msg,
    MsgType type,
    std::string component, 
    std::string filePath,
    int line,
    int index
) noexcept {
    m_debugger->stEcho(type, msg, component, filePath, line, index);
}