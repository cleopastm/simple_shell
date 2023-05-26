#include "shell.h"
#define MAX_ALIAS_LENGTH 100
#define MAX_ARGUMENTS 100

/**
* replace_variables - replacing variables
* @command: pointer
*
* Return: 0
*/


void replace_variables(char *command)
{
	char *pos;
	char variable[MAX_ALIAS_LENGTH];
	char *value;

	while ((pos = strstr(command, "$?")) != NULL)
	{
		snprintf(variable, sizeof(variable), "%d", last_command_status);
		value = variable;
		replace_string(command, pos, 2, value);
	}
	while ((pos = strstr(command, "$$")) != NULL)
	{
		snprintf(variable, sizeof(variable), "%d", getpid());
		value = variable;
		replace_string(command, pos, 2, value);
	}
}

/**
 * main - holding co functions of homeshell
 * @argv: argument vector
 * @ac: pointer args
 *
 * Return: o
 */

int main(void) /*int ac, char **argv*/
{
	/*char *prompt = "#HomeShell:~ $ ";*/
	char *cmd = NULL;
	size_t len = 0;
	ssize_t az;
	int i;
	int skip_first_line = 0;
	/*char *err_msg = "No such file or directory";*/

	int devNull = open("/dev/null", O_WRONLY);

	if (devNull == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(devNull, STDERR_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(devNull);

	while (1)
	{
		char *command_path;

		/*write(STDOUT_FILENO, prompt, strlen(prompt));*/
		az = getline(&cmd, &len, stdin);
		

		if (az == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		i = az - 1;
		cmd[i] = '\0';

		if (skip_first_line == 1)
		{
			skip_first_line = 0;
			continue;
		}

		if (strcmp(cmd, "/bin/ls") != 0)
		{
			if (write(STDOUT_FILENO, cmd, strlen(cmd)) == -1)
			{
				perror("write");
				exit(EXIT_FAILURE);
			}
		}
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		if (strncmp(cmd, "exit", 4) == 0)
		{
			/*char *arg = strtok(cmd + 4, " ");*/

			handle_exit(cmd);
		}
		else if (strncmp(cmd, "#", 1) == 0)
		{
			continue;
		}
		else if (strncmp(cmd, "cd", 2) == 0)
		{
			char *dir = strtok(cmd + 3, " ");

			if (dir != NULL)
			{
				if (chdir(dir) != 0)
				{
					perror("chdir");
				}
			}
			else
			{
				fprintf(stderr, "Invalid cd command\n");
			}
		}
		else
		{
			char *args[MAX_ARGUMENTS];
			char *token = strtok(cmd, " ");

			i = 0;
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			replace_variables(cmd);
			command_path = args[0];
			handle_exec(command_path, args);
		}
	}
	memset(cmd, 0, len);
	free(cmd);
	return (0);
}
