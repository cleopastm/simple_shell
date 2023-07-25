#include "shell.h"

/**
 * main - main function
 *
 * Return: 0
 */

int main(void)
{
	char *commands[MAX_COMMANDS];
	char *arguments[MAX_ARGUMENTS];
	int interactive = isatty(STDIN_FILENO);
	char *cmd, *command;
	char *status;
	char *variable;
	char *value;
	char *directory;
	size_t len;
	int i;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);  /* Display prompt*/
		cmd = my_getline();
		if (cmd == NULL)
			break;

		len = strlen(cmd);
		if (len > 0 && cmd[len - 1] == '\n')
		cmd[len - 1] = '\0';
		parse_cmd(cmd, commands);
		for (i = 0; commands[i] != NULL; i++)
		{
			command = commands[i];
			parse_args(command, arguments);
			if (strcmp(arguments[0], "exit") == 0)
			{
				/* Handle exit command with status argument*/
				status = arguments[1];
				if (status == NULL)
					execute_exit("0");  /* Default exit status is 0*/
				else
					execute_exit(status);
				break; /* Exit the shell immediately after handling the "exit" command*/
			}
			else if (strcmp(arguments[0], "env") == 0)
			{
				execute_env();  /* Execute env built-in command*/
			}
			else if (strcmp(arguments[0], "setenv") == 0)
			{
				/* Handle setenv command*/

				variable = arguments[1];
				value = arguments[2];
				if (variable != NULL && value != NULL)
					execute_setenv(variable, value);
				else
					fprintf(stderr, "Invalid setenv command\n");
			}
			else if (strcmp(arguments[0], "unsetenv") == 0)
			{
				/* Handle unsetenv command*/
				variable = arguments[1];
				if (variable != NULL)
					execute_unsetenv(variable);
				else
					fprintf(stderr, "Invalid unsetenv command\n");
			}
			else if (strcmp(arguments[0], "cd") == 0)
			{
				/*Handle cd command*/
				directory = arguments[1];
				execute_cd(directory);
			}
			else
			{
				if (execute_command(arguments[0], arguments) == -1)
				{
					fprintf(stderr, "Failed to execute command: %s\n", command);
				}
			}
		}
		free(cmd);
	}
	return (0);
}
