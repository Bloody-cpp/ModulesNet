#include "include.h"
#include <cstddef>
#include <headerParse.h>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace mnet;
using namespace std;

HeaderFabric::HeaderFabric(Cleaner& cleaner) noexcept 
    : m_cleaner((cleaner)){}

void HeaderFabric::parseTargetHeader(std::string& code, file_t file, Header& header) {
    const string moduleLiteral = "@module";
    const string applicationLiteral = "@application";

    auto instance = m_cleaner.makeRemoveLiterals(code);
    size_t moduleIndex = instance.find(moduleLiteral);
    size_t applicationIndex = instance.find(applicationLiteral);

    if (moduleIndex != string::npos && applicationIndex != string::npos) {
        cout << "[" << file.m_path << "] " << "two compile target" << endl;
        exit(-2);
    }

    const size_t doubleModuleIndex = moduleIndex + moduleLiteral.size();
    const size_t doubleApplicationIndex = applicationIndex + applicationLiteral.size();

    //Check for double define target
    if (instance.find(moduleLiteral, doubleModuleIndex) != string::npos ||
        instance.find(applicationLiteral, doubleApplicationIndex) != string::npos) {
        cout << "[" << file.m_path << "] " << "must have one compile target define" << endl;
        exit(-1);
    }
    if (applicationIndex != string::npos) {
        header.m_mode = tokenProperties::APPLICATION;
        return;
    }

    moduleIndex += string("#module").size();
    for (size_t x = moduleIndex; x < instance.size(); x++) {
        if (instance[x] == '\n')
            break;
        if (instance[x] == ' ' && header.m_targetName.size() != 0)
            break;
        if (instance[x] == ' ')
            continue;
        header.m_targetName.push_back(instance[x]);
    }
    if (header.m_targetName.size() == 0) {
        cout << "[" << file.m_path << "] " << "must have compile target name" << endl;
        exit(-3);
    }
}
void HeaderFabric::parseRequires(std::string& code, file_t file, Header& header) {
    return;
}
void HeaderFabric::parseIncludes(std::string& code, file_t file, Header& header) {
    return;
}
Header HeaderFabric::parseFrom(std::string& code, file_t file) {
    Header header;
    parseTargetHeader(code, file, header);
    parseRequires(code, file, header);
    parseIncludes(code, file, header);
    return std::move(header);
}
