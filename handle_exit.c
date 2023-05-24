#include "shell.h"

/**
 * handle_exit - handlinhg the exit command
 * @cmd: a poinder to the commmand prompt
 *
 * Return: void
 */

void handle_exit(char *cmd)
{
	char *status_str = strtok(cmd, " ");

	status_str = strtok(NULL, " ");
	if (status_str != NULL)
	{
		int status = atoi(status_str);

		exit(status);
	}
	else
	{
		exit(0);
	}
}
