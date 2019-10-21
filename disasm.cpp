#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define $assert(cond, code)                                                             \
    if (!cond)                                                                          \
    {                                                                                   \
        fprintf (stderr, "something is not OK in %d string\n",  __LINE__);                \
        code;                                                                           \
    }

const char* COMMANDS = "code.bin";
const char* OUTPUT_FILE = "disasmed.txt";

int* read_binary_code ( long &file_size );

void write_cmd (int* cmd, long cmd_num);

int main ()
{
    long cmd_num = 0;
    int* code = read_binary_code (cmd_num);
    cmd_num /= 4;
    write_cmd (code, cmd_num);
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


void write_cmd (int* cmd, long cmd_num)
{
    FILE* stream = fopen (OUTPUT_FILE, "w");

    #define DEF_CMD(name, num, argc, code)                                       \
        else if (cmd[i] == num)                                                  \
        {                                                                        \
            fprintf (stream, "%s ", #name);                                       \
            if (argc == 1)                                                       \
                fprintf (stream, "%d.%d\n", cmd[i+1] / 100, cmd[i+1] % 100);     \
            else                                                                 \
                fprintf (stream, "\n");                                          \
         }

    for (int i = 0; i < cmd_num; i+=2)
    {
        if (false) ;

        #include "commands.hpp"

        else
            fprintf (stderr, "\nWRONG COMMAND!\n"
                             "String of wrong command in file: %d\n\n", i+1);
    }
    #undef DEF_CMD
}

