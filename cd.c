
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
/**
 * execute_cd - function to change directory
 * @directory: pointer to current directory
 *
 * Return - o
 */

void execute_cd(const char *directory)
{
	char *dir = NULL;
	char *current_dir;
	char *new_dir;

	if (directory == NULL || strcmp(directory, "-") == 0)
	{
		/* Handle "cd -" or "cd" (no argument)*/

		dir = getenv("OLDPWD");

		if (dir == NULL)
		{
			fprintf(stderr, "No previous directory stored in OLDPWD\n");
			return;
		}
	}
	else
	{
		/* Handle regular "cd" command with an argument*/
		dir = strdup(directory);
	}
	/*Store the current directory in OLDPWD*/
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("getcwd");
		free(dir);
		return;
	}
	if (setenv("OLDPWD", current_dir, 1) != 0)
	{
		perror("setenv");
		free(dir);
		free(current_dir);
		return;
	}
	free(current_dir);
	/* Change directory*/
	if (chdir(dir) != 0)
	{
		perror("chdir");
		free(dir);
		return;
	}
	free(dir);
	/* Update the PWD environment variable*/
	new_dir = getcwd(NULL, 0);
	if (new_dir == NULL)
	{
		perror("getcwd");
		return;
	}
	if (setenv("PWD", new_dir, 1) != 0)
	{
		perror("setenv");
		free(new_dir);
		return;
	}
	free(new_dir);
}
