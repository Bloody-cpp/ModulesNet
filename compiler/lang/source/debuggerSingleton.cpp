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