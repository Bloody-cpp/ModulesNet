#ifndef COMPILER_INCLUDE_FILE
#define COMPILER_INCLUDE_FILE

#include <string>
#include <fstream>
#include <exception>
#include <sstream>

namespace mnet {
    class File {
        std::ifstream m_file;
        std::string m_path;
    public:
        File() noexcept = default;
        File(const std::string path);
        ~File() noexcept;

        void openFile(std::string path);
        std::string get();
    };
}

#endif /* COMPILER_INCLUDE_FILE */
