#include "../include/filesManager.h"
#include "../lang/include/debuggerSingleton.h"
#include <iostream>

using namespace mnet::fs;
using namespace std;

namespace mnet {
    bool validate(const string path) noexcept {
        return exists(path);
    }
    void validate(const vector<string> paths, string handle) noexcept {
        for (auto path : paths) {
            if (!exists(path)) {
                DebuggerSingleton::echo("is not exists", error, handle, path);
            }
        }
    }
    bool compareExtension(path path, string extension) noexcept {
        return path.extension() == extension;
    }
    bool compareFilename(path path, string filename) noexcept {
        return path.filename() == filename;
    }
    string getFileName(path path) noexcept {
        return path.filename().u8string();
    }
}