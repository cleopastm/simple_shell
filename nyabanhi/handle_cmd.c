#include "shell.h"

/**
 * handle_command - Handle a single command.
 * @args: The arguments array for the command.
 */
void handle_command(char **args)
{
    // Check if the command ends with a logical operator
    int argCount = 0;
    while (args[argCount] != NULL)
        argCount++;

    int last_arg_index = argCount - 1;
    int is_logical_operator = 0;
    if (last_arg_index >= 0)
    {
        if (strcmp(args[last_arg_index], "&&") == 0 || strcmp(args[last_arg_index], "||") == 0)
        {
            is_logical_operator = 1;
        }
    }

    // Handle logical operators
    if (is_logical_operator)
    {
        // Execute the command before the logical operator
        args[last_arg_index] = NULL; // Remove the logical operator from the arguments
        execute_command(args);

        // Check the return status of the previous command
        int status;
        wait(&status);

        if (strcmp(args[last_arg_index], "&&") == 0)
        {
            // Execute the next command if the previous command succeeded
            if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
            {
                // Move to the next command
                last_arg_index++;
                args[last_arg_index] = NULL; // Remove the logical operator from the arguments
                handle_command(args);
            }
        }
        else if (strcmp(args[last_arg_index], "||") == 0)
        {
            // Execute the next command if the previous command failed
            if (!(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS))
            {
                // Move to the next command
                last_arg_index++;
                args[last_arg_index] = NULL; // Remove the logical operator from the arguments
                handle_command(args);
            }
        }
    }
    else
    {
        // Execute the command without any logical operator
        execute_command(args);
    }
}

