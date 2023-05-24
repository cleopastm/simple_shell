#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shell.h"

/**
 * exit_shell - Exit the shell with a specific status code.
 * @status: The status code to exit the shell with.
 */
void exit_shell(int status)
{
    write(STDOUT_FILENO, "Exiting shell...\n", 17);
    exit(status);
}

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
        characters = read(STDIN_FILENO, buffer, bufsize);  // Read command line

        if (characters == -1)
        {
            perror("read error");
            exit(EXIT_FAILURE);
        }

        buffer[characters - 1] = '\0';  // Remove newline character

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
            if (argCount > 2)
            {
                write(STDOUT_FILENO, "Usage: exit [status]\n", 21);
            }
            else if (argCount == 2)
            {
                int status = atoi(args[1]);
                exit_shell(status);
            }
            else
            {
                exit_shell(EXIT_SUCCESS);
            }
        }

        // ... handle other commands ...

    }

    free(buffer);
    return 0;
}

