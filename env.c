#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * execute_setenv - function to set env
 * @variable: a pointer to variable to be assigned
 * @value: a pointer to the assigned value
 *
 * Return - 0
 */

void execute_setenv(const char *variable, const char *value)
{
	if (setenv(variable, value, 1) != 0)
	{
		fprintf(stderr, "Failed to set environment variable: %s\n", variable);
	}
}

/**
 * execute_unsetenv - fnction to unset env
 * @variable: pointer to previously assigned variable
 *
 * Return - 0
 */

void execute_unsetenv(const char *variable)
{
	if (unsetenv(variable) != 0)
	{
		fprintf(stderr, "Failed to unset environment variable: %s\n", variable);
	}
}


