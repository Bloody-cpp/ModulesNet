#include "../include/filesManager.h"
#include <iostream>

using namespace mnet::fs;
using namespace std;

namespace mnet {
    bool validate(const string path) noexcept {
        return exists(path);
    }
    bool validate(const vector<string> paths, string handle) noexcept {
        bool state = true;
        for (auto path : paths) {
            if (!exists(path)) {
                cout << "[" + handle + "] " + path + " is not exists" << endl;
                state = false;
            }
        }
        return state;
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