#include <file.h>
#include <filesystem>
#include <stdexcept>
#include "../include/filesManager.h"
#include "../lang/include/debuggerSingleton.h"

using namespace mnet;
using namespace std;

File::File(const string path) {
    m_path = path;
    openFile(path);
}
void File::openFile(const string path) {
    m_file.open(path);
    if (m_file.fail())
        DebuggerSingleton::echo("Can`t open file", error, "File", path);
}
string File::get() {
    if (!m_file.is_open())
        DebuggerSingleton::echo("File don`t open", error, "File", m_path);
    return string((std::istreambuf_iterator<char>(m_file)),
                  (std::istreambuf_iterator<char>()));
}
file_t File::convert() {
    if (!m_file.is_open())
        DebuggerSingleton::echo("File don`t open", error, "File", m_path);
    file_t instance;
    instance.m_path = m_path;
    instance.m_code = get();
    instance.m_name = getFileName(instance.m_path);
    return instance;
}
File::~File() noexcept {
    if (m_file.is_open())
        m_file.close();
}