#ifndef LANG_INCLUDE_LANGPARSER
#define LANG_INCLUDE_LANGPARSER

#include <vector>
#include <string>

namespace mnet
{
    class LangParser {
        
    public:
        LangParser() noexcept = default;
        ~LangParser() noexcept = default;

        void parse(const std::string& code) noexcept;
    };
}

#endif /* LANG_INCLUDE_LANGPARSER */
