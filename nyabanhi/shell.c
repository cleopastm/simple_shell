#include "shell.h"

/**
 * exit_shell - Exit the shell.
 */
void exit_shell()
{
    write(STDOUT_FILENO, "Exiting shell...\n", 17);
    exit(EXIT_SUCCESS);
}
/**
 * main - Entry point for the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
    char *buffer;
    size_t bufsize = 1024;
    ssize_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        write(STDOUT_FILENO, "#myShell$ ", 10);  // Display prompt
        characters = getline(&buffer, &bufsize, stdin);  // Read command line

        if (characters == -1)
        {
            if (feof(stdin))
            {
                write(STDOUT_FILENO, "\n", 1);
                break;
            }
            perror("getline error");
            exit(EXIT_FAILURE);
        }

        buffer[characters - 1] = '\0';  // Remove newline character

        // Skip lines starting with '#'
        if (buffer[0] == '#')
            continue;

        char *token;
        char *args[100];
        int argCount = 0;

        token = strtok(buffer, " ");
        while (token != NULL)
        {
            args[argCount++] = token;
            token = strtok(NULL, " ");
        }
        args[argCount] = NULL;

        if (strcmp(args[0], "exit") == 0)
        {
            exit_shell();
        }
        else if (strcmp(args[0], "setenv") == 0)
        {
            if (set_env(args) == -1)
            {
                // Handle setenv failure
            }
        }
        else if (strcmp(args[0], "unsetenv") == 0)
        {
            if (unset_env(args) == -1)
            {
                // Handle unsetenv failure
            }
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            cd(args);
        }
        else
        {
            execute_command(args);
        }
    }

    free(buffer);
    return 0;
}

