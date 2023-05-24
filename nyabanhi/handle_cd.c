#include "shell.h"

/**
 * cd - Change directory.
 * @args: Array of command line arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int cd(char *args[])
{
	if (args[1] == NULL)
	{
		/* No directory specified, change to the home directory */
		const char *home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			perror("cd: HOME not set");
			return -1;
		}

		if (chdir(home_dir) == -1)
		{
			perror("cd");
			return -1;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		/* Change to the previous directory */
		const char *prev_dir = getenv("OLDPWD");
		if (prev_dir == NULL)
		{
			perror("cd: OLDPWD not set");
			return -1;
		}

		if (chdir(prev_dir) == -1)
		{
			perror("cd");
			return -1;
		}
	}
	else
	{
		/* Change to the specified directory */
		if (chdir(args[1]) == -1)
		{
			perror("cd");
			return -1;
		}
	}

	/* Update the PWD environment variable */
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return -1;
	}

	if (setenv("PWD", cwd, 1) == -1)
	{
		perror("setenv");
		return -1;
	}

	return 0;
}

