#include "shell.h"

int last_command_status = 0;

void replace_string(char *str, char *pos, int len, char *value) {
    int value_len = strlen(value);
    int new_len = strlen(str) - len + value_len;

    // Shift the string to the right to make room for the replacement value
    memmove(pos + value_len, pos + len, new_len - (pos - str));

    // Copy the replacement value into the string
    memcpy(pos, value, value_len);
}


void replace_variables(char *command) {
    char *pos; // Position of the variable
    char variable[MAX_ALIAS_LENGTH]; // Variable name
    char *value; // Value of the variable

    // Replace $? with the exit status of the last command
    while ((pos = strstr(command, "$?")) != NULL) {
        snprintf(variable, sizeof(variable), "%d", last_command_status);
        value = variable;
        replace_string(command, pos, 2, value);
    }


    // Replace $$ with the process ID of the shell
    while ((pos = strstr(command, "$$")) != NULL) {
        snprintf(variable, sizeof(variable), "%d", getpid());
        value = variable;
        replace_string(command, pos, 2, value);
    }
}

void handle_exit(char *cmd) {
    // Extract the exit status from the command
    char *status_str = strtok(cmd, " ");
    status_str = strtok(NULL, " ");
    // Check if an exit status is provided
    if (status_str != NULL) {
        int status = atoi(status_str);
        exit(status);
    } else {
        exit(0);
    }
}



int main(int ac, char **argv)
{
	char *prompt = "#HomeShell:~ $ ";
	char *cmd = NULL;
	size_t len = 0;
	ssize_t az;
	int i;
	char *err_msg = "No such file or directory";

	while (1) {
		/* Print prompt and read user input */
		write(STDOUT_FILENO, prompt, strlen(prompt));
		az = getline(&cmd, &len, stdin);
	char *command_path;
	if (az == -1)
	{
			perror("getline");
			exit(EXIT_FAILURE);
	}
		/* Remove newline character from input */
		i = az - 1;
		cmd[az - 1] = '\0';
	/* Check if user entered exit command */
	if (strncmp(cmd, "exit", 4) == 0)
	{
		   char *arg = strtok(cmd + 4, " ");
	   handle_exit(cmd);
	} else if (strncmp(cmd, "#", 1) == 0)
	{
			// Skip comments, continue to the next iteration
			continue;
		} else if (strncmp(cmd, "cd", 2) == 0) {
			/* Handle cd command */
			char *dir = strtok(cmd + 3, " ");
			if (dir != NULL) {
				if (chdir(dir) != 0) {
					perror("chdir");
				}
			} else {
				fprintf(stderr, "Invalid cd command\n");
			}
		} else if (strncmp(cmd, "env", 3) == 0) {
			/* Get environment variables */
			extern char **environ;
			char **env = environ;
			/* Loop through environment variables and print them out */
			while (*env != NULL) {
				write(STDOUT_FILENO, *env, strlen(*env));
				write(STDOUT_FILENO, "\n", 1);
				env++;
			}
		} else if (strncmp(cmd, "setenv", 6) == 0) {
			char *var = strtok(cmd + 7, " ");
			char *value = strtok(NULL, " ");
			if (var != NULL && value != NULL) {
				if (setenv(var, value, 1) == -1) {
					fprintf(stderr, "Failed to set environment variable\n");
				}
			} else {
				fprintf(stderr, "Invalid setenv command\n");
			}
		} else if (strncmp(cmd, "unsetenv", 8) == 0) {
			char *var = strtok(cmd + 9, " ");
			if (var != NULL) {
				if (unsetenv(var) == -1) {
					fprintf(stderr, "Failed to unset environment variable\n");
				}
			} else {
				fprintf(stderr, "Invalid unsetenv command\n");
			}
		} else if (strncmp(cmd, "alias", 5) == 0) {
			handle_alias(cmd + 6);
		} else {
			/* Parse commands separated by ; */
			char *command = strtok(cmd, ";");
			while (command != NULL) {
				/* Trim leading and trailing whitespaces */
				while (*command == ' ') {
					command++;
				}
				i = strlen(command) - 1;
				while (command[i] == ' ') {
					command[i] = '\0';
					i--;
				}
				/* Execute the command */
				char *args[MAX_ARGUMENTS];
				int num_args = 0;
				args[num_args] = strtok(command, " ");
				while (args[num_args] != NULL && num_args < MAX_ARGUMENTS - 1) {
					num_args++;
					args[num_args] = strtok(NULL, " ");
				}
				args[num_args] = NULL;
				/* Check if command is in /bin directory */
				if (strncmp(args[0], "/", 1) == 0) {
					command_path = args[0];
				} else {
					command_path = get_command_path(args[0]);
					if (command_path == NULL) {
						fprintf(stderr, "%s\n", err_msg);
						break;
					}
				}
				handle_exec(command_path, args);
				/* Move to the next command */
				command = strtok(NULL, ";");
			}

		}
	}
	return 0;
}
