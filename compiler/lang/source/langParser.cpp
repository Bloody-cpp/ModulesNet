#include "../include/langParser.h"
#include "include.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <unordered_map>

using namespace mnet;
using namespace std;

LangParser::LangParser() noexcept {}

shared_ptr<parsing::Lines> LangParser::makeLines(std::string& code) noexcept {
    setDebugInfo({&m_structure->m_file, "Getting lines of file"});
    shared_ptr<parsing::Lines> returnLines = make_shared<parsing::Lines>();

    vector<string> lines;
    boost::split(lines, code, boost::is_any_of("\n"));
    for (size_t x = 0; x < lines.size(); x++) {
        if (lines[x].find('@') != string::npos) {
            if (lines[x][0] != '@')
                echo("mnet keyword must be in begin of line", error, x + 1, lines[x].find('@') + 1);
            if (lines[x].find('@', lines[x].find('@') + 1) != string::npos)
                echo("has double keyword", error, x + 1, lines[x].find('@') + 1);
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
            if (literals.empty())
                echo("Module must have name", error, line.second);
            if (literals.size() > 2)
                echo("Module must have name without spaces", error, line.second);
            m_structure->m_targetName = literals[1];
        }
        if (keyword == parsing::Application) {
            hasApplication = true;
            m_structure->m_mode = tokenProperties::Application;
        }
        if (!hasModule && !hasApplication)
            echo("Compile target don`t detect", error);
    }
}

void LangParser::parseRequires() noexcept {
    
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

    //Parsing header of file
    setDebugInfo({&m_structure->m_file, "Header parsing"});
    parseCompileTarget();
    parseRequires();
    parseIncludes();

    return m_structure;
}