#include "shell.h"

/**
 * get_command_path - to get the path to an command
 * @command: pointer to to a command
 * Return: 0
 */


char *get_command_path(const char *command)
{
	char *path = getenv("PATH");
	char *token, *command_path;
	int command_path_len;

	token = strtok(path, ":");
	while (token != NULL)
	{
		command_path_len = snprintf(NULL, 0, "%s/%s", token, command) + 1;
		command_path = malloc(command_path_len);
		if (command_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		snprintf(command_path, command_path_len, "%s/%s", token, command);
		if (access(command_path, F_OK) == 0)
		{
			return (command_path);
		}
		free(command_path);
		token = strtok(NULL, ":");
	}
	return (NULL);
}
