#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * replace_variable - Replace a variable with a value in an argument array.
 * @args: The argument array.
 * @variable: The variable to replace.
 * @value: The value to replace with.
 *
 * Description: This function replaces occurrences of a variable with a value
 *              in the given argument array.
 */
void replace_variable(char **args, const char *variable, const char *value)
{
    // Check if the variable is an empty string
    if (variable[0] == '\0') {
        return;
    }

    int i = 0;
    while (args[i] != NULL)
    {
        // Find the first occurrence of the variable in the argument
        char *ptr = strstr(args[i], variable);
        while (ptr != NULL)
        {
            // Check if the variable is a standalone word
            if ((ptr == args[i] || !isalnum(*(ptr - 1))) &&
                !isalnum(*(ptr + strlen(variable))))
            {
                // Calculate the length of the replaced argument
                size_t var_len = strlen(variable);
                size_t value_len = strlen(value);
                size_t arg_len = strlen(args[i]);
                size_t new_arg_len = arg_len - var_len + value_len;

                // Allocate memory for the new argument
                char *new_arg = (char *)malloc((new_arg_len + 1) * sizeof(char));
                if (new_arg == NULL)
                {
                    perror("malloc error");
                    exit(EXIT_FAILURE);
                }

                // Copy the parts before the variable
                strncpy(new_arg, args[i], ptr - args[i]);
                new_arg[ptr - args[i]] = '\0';

                // Concatenate the value
                strcat(new_arg, value);

                // Copy the rest of the argument
                strcat(new_arg, ptr + var_len);

                // Free the old argument and assign the new one
                free(args[i]);
                args[i] = new_arg;

                // Move to the next occurrence of the variable
                ptr = strstr(args[i], variable);
            }
            else
            {
                // Move to the next character in the argument
                ptr++;
            }
        }
        i++;
    }
}

