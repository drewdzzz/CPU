/// @file Compiler + executor
#include <stdlib.h>

///@brief Define COMPILE if want to Compile before execution
#define COMPILE

#ifdef COMPILE
    #define MAKE(asm,cpu)       \
        system ("mingw32-g++.exe " #asm ".cpp" " -o " #asm ".exe");   \
        system ("mingw32-g++.exe " #cpu ".cpp" " -o " #cpu ".exe");   \
        system ("cls");         \
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
