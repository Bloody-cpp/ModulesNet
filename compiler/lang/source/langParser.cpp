#include "../include/langParser.h"
#include "include.h"
#include <boost/algorithm/string.hpp>
#include <filesystem>
#include <algorithm>
#include <unordered_map>

using namespace mnet;
using namespace std;

LangParser::LangParser() noexcept {}

shared_ptr<parsing::Lines> LangParser::makeLines(std::string& code, const char prefix) noexcept {
    setDebugInfo({&m_structure->m_file, "Getting lines of file"});
    shared_ptr<parsing::Lines> returnLines = make_shared<parsing::Lines>();

    vector<string> lines;
    boost::split(lines, code, boost::is_any_of("\n"));
    for (size_t x = 0; x < lines.size(); x++) {
        if (lines[x].find(prefix) != string::npos) {
            if (lines[x][0] != prefix)
                echo("mnet keyword must be in begin of line", error, x + 1, lines[x].find(prefix) + 1);
            if (lines[x].find(prefix, lines[x].find(prefix) + 1) != string::npos)
                echo("has double keyword", error, x + 1, lines[x].find(prefix) + 1);
            (*returnLines.get())[lines[x]] = x + 1;
        }
    }
    return returnLines;
}

vector<string> LangParser::getLiterals(const string line) noexcept {
    vector<string> literals;
    boost::split(literals, line, boost::is_any_of(" "));
    return literals;
}

parsing::LangKeywords LangParser::getKeyword(const string line) noexcept {
    static const std::unordered_map<string, parsing::LangKeywords> associations = {
        {"@application", parsing::Application},
        {"@module", parsing::Module},
        {"@event", parsing::Event},
        {"@global-event", parsing::GlobalEvent},
        {"@external", parsing::Extern},
        {"@public", parsing::Public},
        {"@require", parsing::Require}
    };

    auto literals = getLiterals(line);
    if (literals.empty())
        return parsing::UnknowSymbol;
    for (auto lit : literals) {
        if (associations.count(lit) == 0) 
            return parsing::UnknowSymbol;
        return associations.find(lit)->second;
    }
    return parsing::UnknowSymbol;
}

string LangParser::getPath(const std::string literal, const size_t lineNumber) noexcept {
    string str = getString(literal, lineNumber);
    if (!filesystem::exists(str))
        echo("Path is not exists", error, lineNumber);
    return str;
}

string LangParser::getString(const std::string literal, const size_t lineNumber) noexcept {
    size_t begin = literal.find('<');
    size_t end = literal.find('>');
    if (begin == string::npos || end == string::npos)
        echo("Cannot find begin '<' and end '>'", error, lineNumber);
    if (literal.find('<', begin + 1) != string::npos || literal.find('>', end + 1) != string::npos)
        echo("Incorrect string", error, lineNumber);
    if (begin + 1 == end)
        echo("Empty string", error, lineNumber);
    return literal.substr(begin + 1, end - begin - 1);
}

void LangParser::parseCompileTarget() noexcept {
    bool hasModule = false;
    bool hasApplication = false;
    for (auto line : *m_noLiteralsLines) {
        auto keyword = getKeyword(line.first);
        if (keyword == parsing::UnknowSymbol)
            echo("Unknow symbol", error, line.second);
        if (keyword == parsing::Module || keyword == parsing::Application) {
            if (hasModule || hasApplication)
                echo("Double define compile target", error, line.second);
        }
        if (keyword == parsing::Module) {
            hasModule = true;
            m_structure->m_mode = tokenProperties::Module;
            auto literals = getLiterals(line.first);
            if (literals.size() == 1)
                echo("Module must have name", error, line.second);
            if (literals.size() > 2)
                echo("Module must have name without spaces", error, line.second);
            m_structure->m_targetName = literals[1];
        }
        if (keyword == parsing::Application) {
            hasApplication = true;
            m_structure->m_mode = tokenProperties::Application;
        }
    }
    if (!hasModule && !hasApplication)
        echo("Compile target don`t detect", error);
}

void LangParser::parseRequires() noexcept {
    for (auto line : *m_noLiteralsLines) {
        auto keyword = getKeyword(line.first);
        if (keyword == parsing::Require) {
            auto literals = getLiterals(line.first);
            if (literals.size() == 1)
                echo("Missed module name", error, line.second);
            if (literals.size() > 2)
                echo("Module must have name without spaces", error, line.second);
            string requireModuleName = getString(literals[1], line.second);
            auto& requiresLink = m_structure->m_requires;
            if (find(requiresLink.begin(), requiresLink.end(), requireModuleName) == requiresLink.end())
                requiresLink.push_back(requireModuleName);
        }
    }
}
void LangParser::parseIncludes() noexcept {
    
}


shared_ptr<FileStructure> LangParser::createStructure(file_t file) noexcept {
    m_cleaner.proccess(file.m_code);
    m_structure = make_shared<FileStructure>();
    m_structure->m_file = file;

    m_lines = makeLines(m_structure->m_file.m_code);

    string noLiteralsInstance = m_cleaner.makeRemoveLiterals(m_structure->m_file.m_code);
    m_noLiteralsLines = makeLines(noLiteralsInstance);
    m_preprocessingLines = makeLines(noLiteralsInstance, '#');

    //Parsing header of file
    setDebugInfo({&m_structure->m_file, "Header parsing"});
    parseCompileTarget();
    parseRequires();
    parseIncludes();

    return m_structure;
}