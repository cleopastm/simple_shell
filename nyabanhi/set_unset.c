#include "shell.h"


/**
 * set_env - Set environment variable.
 * @args: Array of command line arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_env(char *args[])
{
    if (args[1] == NULL || args[2] == NULL)
    {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return -1;
    }

    if (setenv(args[1], args[2], 1) == -1)
    {
        perror("setenv error");
        return -1;
    }

    return 0;
}

/**
 * unset_env - Unset environment variable.
 * @args: Array of command line arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int unset_env(char *args[])
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return -1;
    }

    if (unsetenv(args[1]) == -1)
    {
        perror("unsetenv error");
        return -1;
    }

    return 0;
}

