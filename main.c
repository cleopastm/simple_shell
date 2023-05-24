#include "shell.h"

#define MAX_ALIAS_LENGTH 100
#define MAX_ARGUMENTS 100

int last_command_status = 0;

void replace_variables(char *command, Variable *variables, int num_variables) {
    char *pos; // Position of the variable
    char variable[MAX_VARIABLE_LENGTH + 1]; // Variable name (+1 for null terminator)
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

    // Replace $<variable> with the corresponding value
    for (int i = 0; i < num_variables; i++) {
        snprintf(variable, sizeof(variable), "$%s", variables[i].name);
        value = variables[i].value;
        while ((pos = strstr(command, variable)) != NULL) {
            replace_string(command, pos, strlen(variable), value);
        }
    }
}

    
void handle_exec(char *command_path, char *args[]) {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Child process
        execvp(command_path, args);

        // If execvp returns, an error occurred
        perror(command_path);
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(child_pid, &status, 0);
        set_last_command_status(WEXITSTATUS(status));
    }
}

int main(int ac, char **argv) {
    char *prompt = "#HomeShell:~ $ ";
    char *cmd = NULL;
    size_t len = 0;
    ssize_t az;
    int i;
    char *err_msg = "No such file or directory";
    Variable variables[MAX_VARIABLES];
    int num_variables = 0;	

    while (1) {
        /* Print prompt and read user input */
        write(STDOUT_FILENO, prompt, strlen(prompt));
        az = getline(&cmd, &len, stdin);
        char *command_path;
        if (az == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }
        /* Remove newline character from input */
        i = az - 1;
        cmd[i] = '\0';

        /* Check if user entered exit command */
        if (strncmp(cmd, "exit", 4) == 0) {
            char *arg = strtok(cmd + 4, " ");
            handle_exit(cmd);
        } else if (strncmp(cmd, "#", 1) == 0) {
            // Skip comments
            continue;
        }
        else if (strncmp(cmd, "cd", 2) == 0)
        {
                /* Handle cd command */
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
        } else {
            /* Tokenize command */
            char *args[MAX_ARGUMENTS];
            char *token = strtok(cmd, " ");
            i = 0;

            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            /* Replace variables in the command */
            replace_variables(cmd, variables, num_variables);

            /* Execute command */
            command_path = args[0];
            handle_exec(command_path, args);
        }
    }

    free(cmd);
    return 0;
}

