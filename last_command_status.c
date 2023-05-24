#include "shell.h"


int last_command_status = 0; 

void set_last_command_status(int status)
{
	last_command_status = status;
}

