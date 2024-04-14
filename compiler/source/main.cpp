#include <iostream>
#include <argsParser.h>

using namespace std;

int main(int argc, char **argv)
{
    BNet::ArgsParser argsParser(argc, argv);
    cout << argsParser.getCMakePath() << endl;
    auto args = argsParser.getFilesPaths();
    for (auto arg : args) {
        cout << arg << endl;
    }
    return 0;
}
