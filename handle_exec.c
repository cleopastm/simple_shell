#include "shell.h"

void handle_exec(char *command_path, char *args[])
{
	pid_t pid = fork();

	if (strcmp(args[0], "echo") == 0 && args[1] != NULL && args[1][0] == '$')
	{
		char *variable = args[1] + 1; // Skip the '$' character
		char *value = getenv(variable);
		if (value != NULL)
		{
			write(STDOUT_FILENO, value, strlen(value));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
	{
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process
			execv(command_path, args);
			perror("execv");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent process
			int status;
			waitpid(pid, &status, 0);
			// Set the exit status of the last command
			set_last_command_status(WEXITSTATUS(status));
		}
	}
}
