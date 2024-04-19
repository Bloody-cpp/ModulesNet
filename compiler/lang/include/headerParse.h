#ifndef COMPILER_LANG_INCLUDE_HEADERPARSE
#define COMPILER_LANG_INCLUDE_HEADERPARSE

#include <vector>
#include <string>
#include <unordered_map>
#include "cleaner.h"
#include "include.h"
#include "debuggerSingleton.h"

namespace mnet {
    class HeaderFabric : public DebuggerSingleton {
        Cleaner& m_cleaner;

        void parseTargetHeader(std::string& code, FileStructure& structure);
        void parseRequires(std::string& code, FileStructure& structure);
        void parseIncludes(std::string& code, FileStructure& structure);
    public:
        HeaderFabric(Cleaner& cleaner) noexcept;
        ~HeaderFabric() noexcept = default;

        void apply(FileStructure& structure);
    };
}

#endif /* COMPILER_LANG_INCLUDE_HEADERPARSE */
