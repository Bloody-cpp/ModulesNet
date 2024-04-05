#include <iostream>
#include <argsParser.h>

using namespace std;

int main(int argc, char **argv)
{
    BNet::ArgsParser argsParser(argc, argv);
    cout << argsParser.getCMakePath() << endl;
    cout << argsParser.getCMakeListsPath() << endl;
    return 0;
}
