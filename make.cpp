#include <stdlib.h>

#define COMPILE

#ifdef COMPILE
    #define MAKE(asm,cpu)       \
        system ("mingw32-g++.exe " #asm ".cpp" " -o " #asm ".exe");   \
        system (#cpu ".cpp");   \
        system (#asm ".exe");   \
        system (#cpu ".exe");
#else
    #define MAKE(asm,cpu)       \
        system (#asm ".exe");   \
        system (#cpu ".exe");
#endif


int main()
{
    MAKE(asm,CPU)
}
