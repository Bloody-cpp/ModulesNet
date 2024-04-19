#include "../include/lineParser.h"

using namespace mnet;
using namespace std;

LineParser::LineParser(Cleaner& cleaner) noexcept
    : m_cleaner(cleaner),
    m_headerFabric(cleaner) {}

void LineParser::executeComponents(FileStructure& structure) noexcept {
    m_headerFabric.apply(structure);
}