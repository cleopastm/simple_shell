#include <string.h>
#include "shell.h"

/**
 * parse_cmd - function to pass in commands
 * @cmd: pointer to prompt
 * @args: pointer to pointer of arguments
 *
 * Return: 0
 */

void parse_cmd(char *cmd, char **args)
{
	char *token;
	int i = 0;

	token = strtok(cmd, ";");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, ";");
	}
	args[i] = NULL;
}

/**
 * parse_args - function to parse arguments
 * @cmd: pointer to prompt
 * @args: pointer to arguments
 *
 * Return: 0
 */


void parse_args(char *cmd, char **args)
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
