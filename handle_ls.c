#include "shell.h"

/**
 * handle_ls - for handling ls command
 * @tokens: commands input
 * @num_tokens: number of tokens
 *
 * Return: void
 */

void handle_ls(char **tokens /*int num_tokens*/)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execvp(tokens[0], tokens);

		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

	}
}
