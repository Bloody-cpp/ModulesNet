#include "../include/debuggerSingleton.h"

using namespace mnet;
using namespace std;

void DebuggerSingleton::initializeDebugger(IDebugger *debugger) noexcept {
    m_debugger = debugger;
}

void DebuggerSingleton::setDebugInfo(const DebugInfo info) noexcept {
    m_debugInfo = info;
}

void DebuggerSingleton::echo(string msg, MsgType type) noexcept {
    m_debugger->echo(type, msg, m_debugInfo);
}

void DebuggerSingleton::echo(
    std::string msg,
    MsgType type,
    std::string component, 
    std::string filePath
) noexcept {
    m_debugger->stEcho(type, msg, component, filePath);
}