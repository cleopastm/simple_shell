#include "shell.h"

/**
 * execute_command - function to execute commands
 * @command: pointer to command
 * @args: pointer to arguments
 *
 * Return: 0
 */

int execute_command(const char *command, char *const args[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execvp(command, args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do

		{
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid");
				return (-1);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}

/**
 * execute_env - function to execut env
 *
 * Return: 0
 */

void execute_env(void)
{
	char **env = environ;
	size_t len = strlen(*env);

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * execute_exit - function to execute exit
 * @status: pointer to exit status
 *
 * Return: 0
 */

void execute_exit(const char *status)
{
	int exit_status = atoi(status);

	exit(exit_status);
}
