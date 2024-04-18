#include <cleaner.h>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
using namespace mnet;

string Cleaner::makeRemoveLiterals(std::string& code) noexcept {
    string instance = code;
    size_t begin = instance.find('\"');
    size_t end = instance.find("\"", 1);
    if (begin != string::npos) {
        if (end != string::npos) {
            instance.erase(begin, end - begin + 2);
            makeRemoveLiterals(instance);
        }
    }
    return std::move(instance);
}

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