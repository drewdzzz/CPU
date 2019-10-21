#define DEF_CMD(name, num, argc, code)		\
	CMD_##name = num,

enum commands
{
#include "commands.hpp"
};
#undef DEF_CMD
