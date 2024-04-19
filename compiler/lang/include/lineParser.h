#ifndef COMPILER_LANG_INCLUDE_LINEPARSER
#define COMPILER_LANG_INCLUDE_LINEPARSER

#include <string>
#include <vector>
#include "cleaner.h"
#include "headerParse.h"
#include "include.h"

namespace mnet {
    class LineParser {
        Cleaner& m_cleaner;
        HeaderFabric m_headerFabric;
        FileStructure* m_curFileStructure;
    public:
        LineParser(Cleaner& cleaner) noexcept;
        void executeComponents(FileStructure& structure) noexcept;
    };
}

#endif /* COMPILER_LANG_INCLUDE_LINEPARSER */
