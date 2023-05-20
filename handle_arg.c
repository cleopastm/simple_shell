#include "shell.h"

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
