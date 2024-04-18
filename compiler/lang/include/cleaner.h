#ifndef LANG_INCLUDE_CLEANER
#define LANG_INCLUDE_CLEANER

#include <string>

namespace mnet {
    class Cleaner {
        void deleteSingleComment(std::string& code) noexcept;
        void deleteMultiComment(std::string& code) noexcept;
    public:
        Cleaner() noexcept = default;
        ~Cleaner() noexcept = default;

        void proccess(std::string& code) noexcept;
        std::string makeRemoveLiterals(std::string& code) noexcept;
    };
}

#endif /* LANG_INCLUDE_CLEANER */
