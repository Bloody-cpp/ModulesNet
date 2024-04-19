#ifndef COMPILER_LANG_INCLUDE_LANGPARSER
#define COMPILER_LANG_INCLUDE_LANGPARSER

#include <vector>
#include <string>
#include "cleaner.h"
#include "lineParser.h"
#include "include.h"

namespace mnet
{
    class LangParser {
        Cleaner m_cleaner;
        LineParser m_lineParser;
    public:
        LangParser() noexcept;
        FileStructure parse(file_t file) noexcept;
    };
}

#endif /* COMPILER_LANG_INCLUDE_LANGPARSER */
