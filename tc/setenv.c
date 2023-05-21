#include "shell.h"
/**
 * handle_setenv - Handle the setenv built-in command
 * @tokens: Array of command tokens
 * @num_tokens: Number of tokens
 */
void handle_setenv(char **tokens, int num_tokens)
{
    if (num_tokens < 3)
    {
        perror("setenv: Invalid number of arguments");
        return;
    }
    int ret = setenv(tokens[1], tokens[2], 1);
    if (ret != 0)
    {
        perror("setenv: Failed to set environment variable");
    }
}
/**
 * handle_unsetenv - Handle the unsetenv built-in command
 * @tokens: Array of command tokens
 * @num_tokens: Number of tokens
 */
void handle_unsetenv(char **tokens, int num_tokens)
{
    if (num_tokens < 2)
    {
        perror("unsetenv: Invalid number of arguments");
        return;
    }
    int ret = unsetenv(tokens[1]);
    if (ret != 0)
    {
        perror("unsetenv: Failed to unset environment variable");
    }
}
