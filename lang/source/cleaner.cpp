#include <cleaner.h>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
using namespace mnet;

void Cleaner::deleteSingleComment(string& code) noexcept {
    vector<string> lines;
    boost::split(lines, code, boost::is_any_of("\n"));
    for (size_t x = 0; x < lines.size(); x++) {
        size_t index = lines[x].find("//");
        if (index != string::npos) {\
            lines[x].erase(index, lines[x].size() - index);
            code.clear();
            for (auto z : lines) {
                code += z += '\n';
            }            
            deleteSingleComment(code);
            return;
        }
    }
    return;
}

void Cleaner::deleteMultiComment(string& code) noexcept {
    size_t begin = code.find("/*");
    size_t end = code.find("*/");
    if (begin != string::npos) {
        if (end != string::npos) {
            code.erase(begin, end - begin + 2);
            deleteMultiComment(code);
        }
    }
}

void Cleaner::proccess(string& code) noexcept {
    deleteMultiComment(code);
    deleteSingleComment(code);
}