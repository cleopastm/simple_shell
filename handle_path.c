#include "shell.h"

/**
 * get_command_path - func to search for path
 * @command: a pointr to bthe given command
 * Return: 0
 */

char *get_command_path(char *command)
{
	char *path = getenv("PATH");
	char *dir, *token, *command_path;
	int command_path_len;

	command_path = malloc(sizeof(char) * MAX_PATH_LENGTH);
	if (command_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token = my_strtok(path, ":");
	while (token != NULL)
	{
		command_path_len = snprintf(command_path,
				MAX_PATH_LENGTH, "%s/%s", token, command);
		if (command_path_len >= MAX_PATH_LENGTH)
		{
			fprintf(stderr, "command path too long\n");
			exit(EXIT_FAILURE);
		}
		if (access(command_path, F_OK) == 0)
		{
			return (command_path);
		}
		token = my_strtok(NULL, ":");
	}
	free(command_path);
	return (NULL);
}
