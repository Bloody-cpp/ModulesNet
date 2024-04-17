#ifndef LANG_INCLUDE_TOKEN
#define LANG_INCLUDE_TOKEN

namespace mnet {
    enum TokenType : unsigned short{
        tkFunction = 0,
        tkMethod = 1,
        tkEvent = 2,
        tkPublic = 3,
        tkExternal = 4,
        tkDeclspec = 5,
        tkNoexcept = 6,
        tkStatic = 7,
        tkModule = 8,
        tkApplication = 9,
        tkRequire = 10,
        tkText = 11,
        tkFastCall = 12,
        tkStdCall = 13,
        tkPascal = 14,
        tkCdecl = 15,
        tkThisCall = 16
    };
     
}

#endif /* LANG_INCLUDE_TOKEN */
