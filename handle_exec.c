#include "shell.h"

/**
 * handle_exec - to handle excetions
 * @command_path: pointer to path
 * @args: array of arguments
 * Return: void
 */

void handle_exec(char *command_path, char *args[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execvp(command_path, args);
		perror(command_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		set_last_command_status(WEXITSTATUS(status));
	}
}
