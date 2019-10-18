#include <stdio.h>
#include <string.h>
#include "text_file_worker.hpp"
#include "enum_cmd.hpp"
#include <assert.h>

#define $assert(cond, code)                                                                                   \
    if (!cond)                                                                                                               \
    {                                                                                                                             \
        fprintf (stderr, "something is not OK in %d string",  __LINE__);                     \
        code;                                                                                                                 \
    }

#define DEBUG

#ifdef DEBUG
    #define DEBUG_CODE(code) code;
#else
    #define DEBUG_PRINT(code)
#endif


static const char* INPUT_FILE = "programm_commands.txt";
static const char* OUTPUT_FILE = "code.bin";
static const int MAX_COMMAND_SIZE = 6;

int* cmd_into_buf ( const file_info &command_file);

bool write_cmd (int* cmd_buf, const file_info &input_cmd);

int main ()
{
    const file_info input_cmd = file_worker(INPUT_FILE);

    int* cmd_buf = cmd_into_buf (input_cmd) ;
    $assert (cmd_buf, return 1);

    write_cmd (cmd_buf, input_cmd);

    return 0;
}

int* cmd_into_buf ( const file_info &input_cmd)
{
    int* cmd_buf = (int*) calloc (input_cmd.number_of_strings,  2*sizeof (int));
    $assert(cmd_buf, return nullptr);

    char command_name[MAX_COMMAND_SIZE] = "";
    int command_code = 0;
    int value = 0;

    #define DEF_CMD(name,num, code)                             \
        else if (strcmp (#name, command_name) == 0)       \
        cmd_buf[2*i] = CMD_##name;

    for (long i = 0; i < input_cmd.number_of_strings; i++)
    {
        sscanf (input_cmd.stringpointer[i].b_ptr, " %s", command_name);
        if (false) ;
        #include "commands.hpp"
        else
        {
			fprintf (stderr, "WRONG COMMAND!\n"
                                     "string: %ld\n", i);
            return nullptr;
        }
        sscanf (input_cmd.stringpointer[i].b_ptr, "%*[^0-9]%d", &value);
        cmd_buf[2*i+1] = value;
        value = 0;
    }

    #undef DEF_CMD
    return cmd_buf;
}

bool write_cmd(int* cmd_buf, const file_info &input_cmd)
{
    assert(cmd_buf);

    FILE* output_cmd = fopen (OUTPUT_FILE, "wb");

    $assert(output_cmd, return false);

    fwrite (cmd_buf, 2*sizeof(int), input_cmd.number_of_strings, output_cmd);
    fclose(output_cmd);
    return 1;
}
