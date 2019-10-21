#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "text_file_worker.hpp"

#define $assert(cond, code)                                                                  \
    if (!cond)                                                                               \
    {                                                                                        \
        fprintf (stderr, "something is not OK in %d string",  __LINE__);                     \
        code;                                                                                \
    }

//#define DEBUG

#ifdef DEBUG
    #define DEBUG_CODE(code) code;
#else
    #define DEBUG_CODE(code)
#endif

static const char* INPUT_FILE = "programm_commands.txt";
static const char* OUTPUT_FILE = "code.bin";
static const int MAX_COMMAND_SIZE = 12;
static const int MAX_REG_SIZE = 3;

int* cmd_into_buf ( const file_info &command_file);

bool write_cmd (int* cmd_buf, const file_info &input_cmd);

int cmdcmp (char* string1, char* string2);

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
    float value = 0;
    char reg[MAX_REG_SIZE] = "";

    #define DEF_CMD(name, num, argc, code)                       \
        else if (cmdcmp (#name, command_name) == 0)              \
        cmd_buf[2*i] = num;

    for (long i = 0; i < input_cmd.number_of_strings; i++)
    {
        if ( input_cmd.stringpointer[i].b_ptr[0] == '\0') break;
        sscanf (input_cmd.stringpointer[i].b_ptr, " %s", command_name);
        if (sscanf (input_cmd.stringpointer[i].b_ptr, "%*[^0-9-]%f", &value))
        {
            cmd_buf[2*i+1] = (int) value*100;
            value = 0;
        }
        else if (sscanf (input_cmd.stringpointer[i].b_ptr, "%*[A-Za-z] %s", reg))
        {
            strcat (command_name, " ");
            strcat (command_name, reg);
            strcat (command_name, "\0");
        }
        DEBUG_CODE ( printf ("Command [%d]: %s\n", i, command_name) )

        if (false) ;

        #include "commands.hpp"

        else
        {
			fprintf (stderr, "\nWRONG COMMAND!\n"
                             "String of wrong command in file: %ld\n\n", i+1);
            return nullptr;
        }
    }

    #undef DEF_CMD
    return cmd_buf;
}

bool write_cmd(int* cmd_buf, const file_info &input_cmd)
{
    assert (cmd_buf);

    FILE* output_cmd = fopen (OUTPUT_FILE, "wb");

    $assert(output_cmd, return false);

    fwrite (cmd_buf, 2*sizeof(int), input_cmd.number_of_strings, output_cmd);
    fclose(output_cmd);
    return 1;
}

int cmdcmp (char* string1, char* string2)
{
    assert (string1);
    assert (string2);

    int i = 0;
    while (string1 [i] && string2 [i])
    {
        if ( (string1 [i] == '_' && string2 [i] == ' ') || (string1 [i] == ' ' && string2 [i] == '_') ) ;
        else
            if ( lowercase_letter (string1 [i]) != lowercase_letter (string2 [i]) )
                return lowercase_letter (string1 [i]) - lowercase_letter (string2 [i]);
        i++;
    }
    return lowercase_letter (string1 [i]) - lowercase_letter (string2 [i]);
}
