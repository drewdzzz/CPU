#include <stdio.h>
#include <stdlib.h>
#include "Stack.hpp"
#include "enum_cmd.hpp"

#define $assert(cond, code)                                                             \
    if (!cond)                                                                          \
    {                                                                                   \
        fprintf (stderr, "something is not OK in %d string",  __LINE__);                \
        code;                                                                           \
    }

#define DEBUG

#ifdef DEBUG
    #define DEBUG_CODE(code) code;
#else
    #define DEBUG_PRINT(code)
#endif

const char* COMMANDS = "code.bin";

int* read_binary_code ( long &file_size );

bool CPU_work (long cmd_num, int* code);

int main ()
{
    long cmd_num = 0;
    int* code = read_binary_code (cmd_num);
    cmd_num /= 4;

    $assert(CPU_work (cmd_num, code), return 1)

    return 0;
}

int* read_binary_code ( long &file_size )
{
    FILE* stream = fopen(COMMANDS, "rb");
    if (!stream)
    {
        fprintf (stderr, "Command file can't be opened:(\n");
        abort();
    }
    fseek (stream, 0, SEEK_END);
    file_size = ftell (stream);
    fseek (stream, 0, SEEK_SET);
    int* code = (int*) calloc (file_size,1);
    if (!code)
    {
        fprintf (stderr, "Memory for command buffer can't be allocated:(\n");
        abort();
    }
    fread(code, sizeof (int), file_size / sizeof (int), stream);
    return code;
}

bool CPU_work (long cmd_num, int* code)
{
    Stack_t processor = {};
    SET_NAME(processor);
    ERROR_CODE err_code = OK;
    #define DEF_CMD(name, num, code)        \
        case num: {code;break;}

    for (int i = 0; i < cmd_num; i+=2)
    {
        switch (code[i])
        {
            #include "commands.hpp"
            default: fprintf (stderr, "WRONG_CODE! \n"
                                                  "Command number: %d", i);
                          return false; break;
        }

        DEBUG_CODE (processor.print_stack())
    }
    #undef DEF_CMD
    return true;
}
