#include "../include/langParser.h"
#include "include.h"

using namespace mnet;
using namespace std;

LangParser::LangParser() noexcept
    : m_lineParser(m_cleaner)  {}

FileStructure LangParser::parse(file_t file) noexcept {
    m_cleaner.proccess(file.m_code);

    FileStructure structure;
    structure.m_file = file;

    m_lineParser.executeComponents(structure);
    return structure;
}