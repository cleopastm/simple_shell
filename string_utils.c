#include <ctype.h>
#include "shell.h"

/**
 * trim_whitespace - func to remove white space
 * @str: string pointer
 *
 * Return: 0
 */

char *trim_whitespace(char *str)
{
	while (isspace((unsigned char)*str))
	{
		str++;
	}
	char *end = str + strlen(str) - 1;

	while (end > str && isspace((unsigned char)*end))
	{
		end--;
	}
	*(end + 1) = '\0';
	return (str);
}
