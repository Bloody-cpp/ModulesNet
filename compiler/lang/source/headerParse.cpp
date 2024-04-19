#include "../include/include.h"
#include "debuggerSingleton.h"
#include "../include/headerParse.h"
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace mnet;
using namespace std;

HeaderFabric::HeaderFabric(Cleaner& cleaner) noexcept 
    : m_cleaner((cleaner)) {}
void HeaderFabric::parseTargetHeader(std::string& code, FileStructure& header) {
    const string moduleLiteral = "@module";
    const string applicationLiteral = "@application";

    auto instance = m_cleaner.makeRemoveLiterals(code);
    size_t moduleIndex = instance.find(moduleLiteral);
    size_t applicationIndex = instance.find(applicationLiteral);

    if (moduleIndex != string::npos && applicationIndex != string::npos)
        echo("Two compile target", error);
    if (moduleIndex == string::npos && applicationIndex == string::npos)
        echo("Must have compile target", error);
    const size_t doubleModuleIndex = moduleIndex + moduleLiteral.size();
    const size_t doubleApplicationIndex = applicationIndex + applicationLiteral.size();

    //Check for double define target
    if (instance.find(moduleLiteral, doubleModuleIndex) != string::npos ||
        instance.find(applicationLiteral, doubleApplicationIndex) != string::npos)
        echo("Must have one compile target define", error);

    if (applicationIndex != string::npos) {
        header.m_mode = tokenProperties::APPLICATION;
        return;
    }

    moduleIndex += string(moduleLiteral).size();
    for (size_t x = moduleIndex; x < instance.size(); x++) {
        if (instance[x] == '\n')
            break;
        if (instance[x] == ' ' && header.m_targetName.size() != 0)
            break;
        if (instance[x] == ' ')
            continue;
        header.m_targetName.push_back(instance[x]);
    }
    if (header.m_targetName.size() == 0) 
        echo("Must have compile target name", error);
}
void HeaderFabric::parseRequires(std::string& code, FileStructure& header) {
    return;
}
void HeaderFabric::parseIncludes(std::string& code, FileStructure& header) {
    return;
}
void HeaderFabric::apply(FileStructure& structure) {
    setDebugInfo({&structure.m_file, "HeaderFabric"});
    parseTargetHeader(structure.m_file.m_code, structure);
    parseRequires(structure.m_file.m_code, structure);
    parseIncludes(structure.m_file.m_code, structure);
}
