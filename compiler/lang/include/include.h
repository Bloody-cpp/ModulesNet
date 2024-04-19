#ifndef COMPILER_LANG_INCLUDE_INCLUDE
#define COMPILER_LANG_INCLUDE_INCLUDE

#include <string>
#include <vector>

namespace mnet {
    namespace tokenProperties {
        enum CompileMode : bool {
            MODULE = 0,
            APPLICATION = 1
        };
    }

    typedef struct {
        std::string m_name;
        std::string m_path;
        std::string m_code;
    } file_t;

    struct LineParserCall {
        size_t m_lineNumber;
        file_t m_file;
        std::string m_line;
    };

    struct FileStructure {
        file_t m_file;
        std::string m_targetName;
        tokenProperties::CompileMode m_mode;
        std::vector<std::string> m_requires;
        std::vector<std::string> m_mnetIncludes;
    };
}

#endif /* COMPILER_LANG_INCLUDE_INCLUDE */
