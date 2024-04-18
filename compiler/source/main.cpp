#include <iostream>
#include <argsParser.h>
#include <file.h>
#include <cleaner.h>
#include <headerParse.h>

using namespace std;

int main(int argc, char **argv)
{
    mnet::ArgsParser argsParser(argc, argv);
    mnet::Cleaner cleaner;
    mnet::HeaderFabric header(cleaner);
    auto filesPath = argsParser.getFilesPaths();
    for (auto path : filesPath) {
        mnet::File file(path);

        auto buffer = file.get();
        cleaner.proccess(buffer);
        auto insHeader = header.parseFrom(buffer, file.convert());
        cout << insHeader.m_targetName << endl;
    }
    return 0;
}
