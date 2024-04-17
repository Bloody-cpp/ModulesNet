#include <iostream>
#include <argsParser.h>
#include <file.h>
#include <cleaner.h>

using namespace std;

int main(int argc, char **argv)
{
    mnet::ArgsParser argsParser(argc, argv);
    mnet::Cleaner cleaner;
    auto filesPath = argsParser.getFilesPaths();
    for (auto path : filesPath) {
        mnet::File file(path);
        auto buffer = file.get();

        //for (char x : buffer) {
            //cout << (int)x << " ";
        //}
        cout << endl;

        cleaner.proccess(buffer);

        //for (char x : buffer) {
            //cout << (int)x << " ";
        //}

        cout << endl;
        cout << buffer << endl;
    }
    return 0;
}
