#include "shell.h"


/**
 * check_command - Check if the command exists in PATH.
 * @command: The command to check.
 *
 * Return: The full path to the command if found, NULL otherwise.
 */
char *check_command(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
	char *full_path = (char *)malloc(strlen(dir) + strlen(command) + 2);
	sprintf(full_path, "%s/%s", dir, command);

	if (access(full_path, X_OK) == 0)
	{
	free(path_copy);
	return full_path;
	}
	
	free(full_path);
	dir = strtok(NULL, ":");
	}
	
	free(path_copy);
	return NULL;
}
