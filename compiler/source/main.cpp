#include <iostream>
#include <file.h>
#include "../include/argsParser.h"
#include "../lang/include/langParser.h"
#include "debuggerSingleton.h"
#include "debugger.h"
#include "include.h"

using namespace std;

int main(int argc, char **argv)
{
    mnet::CompilerDebugger debugger;
    mnet::DebuggerSingleton::initializeDebugger(&debugger);

    mnet::ArgsParser argsParser(argc, argv);
    mnet::LangParser parser;
    auto filesPath = argsParser.getFilesPaths();

    vector<mnet::FileStructure> structures;
    for (auto path : filesPath) {
        mnet::File file(path);
        mnet::FileStructure structure = parser.parse(file.convert());
        cout << structure.m_targetName << endl;
        structures.push_back(std::move(structure));
    }
    return 0;
}
