#ifndef COMPILER_LANG_INCLUDE_HEADERPARSE
#define COMPILER_LANG_INCLUDE_HEADERPARSE

#include <vector>
#include <string>
#include <unordered_map>
#include <cleaner.h>
#include <include.h>

namespace mnet {
    class HeaderFabric {
        Cleaner& m_cleaner;

        void parseTargetHeader(std::string& code, file_t file, Header& header);
        void parseRequires(std::string& code, file_t file, Header& header);
        void parseIncludes(std::string& code, file_t file, Header& header);
    public:
        HeaderFabric(Cleaner& cleaner) noexcept;
        ~HeaderFabric() noexcept = default;

        Header parseFrom(std::string& code, file_t file);
    };
}

#endif /* COMPILER_LANG_INCLUDE_HEADERPARSE */
