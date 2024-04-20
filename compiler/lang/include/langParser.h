#ifndef COMPILER_LANG_INCLUDE_LANGPARSER
#define COMPILER_LANG_INCLUDE_LANGPARSER

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "cleaner.h"
#include "include.h"
#include "debuggerSingleton.h"

namespace mnet
{
    namespace parsing {
        typedef std::unordered_map<std::string, size_t> Lines;

        enum LangKeywords : char {
            Module = 0,
            Application = 1,
            Event = 2,
            GlobalEvent = 3,
            Extern = 4,
            Public = 5,
            Require = 6,
            UnknowSymbol = 7
        };
    }

    class LangParser : public DebuggerSingleton{
        Cleaner m_cleaner;
        std::shared_ptr<FileStructure> m_structure; //Updates every call createStructure
        std::shared_ptr<parsing::Lines> m_lines;
        std::shared_ptr<parsing::Lines> m_noLiteralsLines;

        parsing::LangKeywords getKeyword(const std::string line) noexcept;
        std::vector<std::string> getLiterals(const std::string line) noexcept;

        std::shared_ptr<parsing::Lines> makeLines(std::string& code) noexcept;

        void parseCompileTarget() noexcept;       
        void parseRequires() noexcept;
        void parseIncludes() noexcept; 
    public:
        LangParser() noexcept;
        std::shared_ptr<FileStructure> createStructure(file_t file) noexcept;
    };
}

#endif /* COMPILER_LANG_INCLUDE_LANGPARSER */
