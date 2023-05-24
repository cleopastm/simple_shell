#include "shell.h"
#include <ctype.h>

int last_exit_status = 0;

/**
 * replace_variable - Replace a variable with a value in an argument array.
 * @args: The argument array.
 * @variable: The variable to replace.
 * @value: The value to replace with.
 */
void replace_variable(char **args, const char *variable, const char *value)
{
    int i = 0;
    while (args[i] != NULL)
    {
        char *ptr = args[i];
        while ((ptr = strstr(ptr, variable)) != NULL)
        {
            if (ptr == args[i] || !isalnum(*(ptr - 1)))
            {
                size_t var_len = strlen(variable);
                size_t value_len = strlen(value);
                size_t arg_len = strlen(args[i]);
                size_t new_arg_len = arg_len - var_len + value_len;

                char *new_arg = (char *)malloc((new_arg_len + 1) * sizeof(char));
                if (new_arg == NULL)
                {
                    perror("malloc error");
                    exit(EXIT_FAILURE);
                }

                strncpy(new_arg, args[i], ptr - args[i]);
                new_arg[ptr - args[i]] = '\0';

                strcat(new_arg, value);

                strcat(new_arg, ptr + var_len);

                free(args[i]);
                args[i] = new_arg;

                ptr += value_len;
            }
            else
            {
                ptr++;
            }
        }
        i++;
    }
}

/**
 * execute_command - Execute a command.
 * @args: The command and its arguments.
 */
void execute_command(char **args)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /* Child process */
        char exit_status_str[12];
        snprintf(exit_status_str, sizeof(exit_status_str), "%d", last_exit_status);
        replace_variable(args, "$?", exit_status_str);

        char process_id_str[12];
        snprintf(process_id_str, sizeof(process_id_str), "%d", getpid());

        int i = 0;
        while (args[i] != NULL)
        {
            replace_variable(&args[i], "$$", process_id_str);
            i++;
        }

        if (execvp(args[0], args) == -1)
        {
            write(STDOUT_FILENO, "./shell: No such file or directory\n", 35);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
        last_exit_status = WEXITSTATUS(status);
    }
}

/**
 * get_exit_status - Get the exit status of the last command.
 * Return: The exit status as a string.
 */
const char *get_exit_status()
{
    char exit_status_str[12];
    snprintf(exit_status_str, sizeof(exit_status_str), "%d", last_exit_status);
    return strdup(exit_status_str);
}

/**
 * get_process_id - Get the current process ID.
 * Return: The process ID as a string.
 */
const char *get_process_id()
{
    pid_t pid = getpid();
    char process_id_str[12];
    snprintf(process_id_str, sizeof(process_id_str), "%d", pid);
    return strdup(process_id_str);
}

