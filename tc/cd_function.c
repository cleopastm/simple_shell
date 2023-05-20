#include "shell.h"
#include <limits.h>
/**
 * handle_cd - Handle the cd built-in command
 * @tokens: Array of command tokens
 * @num_tokens: Number of tokens
 * @previous_dir: String to store the previous directory path
 * @previous_dir_set: Flag indicating if the previous directory is set
 */
void handle_cd(char **tokens, int num_tokens, char *previous_dir, int *previous_dir_set)
{
    char *target_dir = NULL;
    int stderr_fd = fileno(stderr);
    if (num_tokens < 2 || strcmp(tokens[1], "~") == 0)
    {
        target_dir = getenv("HOME");
    }
    else if (strcmp(tokens[1], "-") == 0)
    {
        if (*previous_dir_set)
        {
            target_dir = previous_dir;
        }
        else
        {
            const char *error_msg = "cd: Previous directory not set\n";
            write(stderr_fd, error_msg, strlen(error_msg));
            return;
        }
    }
    else
    {
        target_dir = tokens[1];
    }
    // Store the current directory as the previous directory
    if (getcwd(previous_dir, PATH_MAX) != NULL)
    {
        *previous_dir_set = 1;
    }
    if (chdir(target_dir) == -1)
    {
        char *error_msg = strerror(errno);
        write(stderr_fd, "cd: ", 4);
        write(stderr_fd, error_msg, strlen(error_msg));
        write(stderr_fd, "\n", 1);
    }
    else
    {
        setenv("PWD", getcwd(NULL, 0), 1);
    }
}

