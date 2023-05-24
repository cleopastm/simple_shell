#include "shell.h"

/**
 * set_last_command_status - function to handle the last command
 * @status: variable to keep track of the last commmand
 *
 * Return: void
 */

void set_last_command_status(int status)
{
	last_command_status = status;
}

