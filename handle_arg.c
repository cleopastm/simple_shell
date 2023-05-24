#include "shell.h"

/**
 * parse_cmd - parsing cmd
 * @cmd: pointer to cmd
 * @args: pointer to a pointer of arguments
 *
 * Return: void
 */

void parse_cmd(char *cmd, char **args)
{
	char *token;
	int i = 0;

	token = strtok(cmd, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
