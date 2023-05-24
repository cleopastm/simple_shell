#include "shell.h"
#include <string.h>

/**
 * replace_string - a function that is used to replace strings
 * @str: a pointer to a string
 * @pos: pointer to position
 * @len: pointer to the string length
 * @value: pointer to the string value
 *
 * Return: void
 */

void replace_string(char *str, char *pos, int len, const char *value)
{
	int value_len = strlen(value);
	int str_len = strlen(str);
	int replace_len = value_len - len;

	memmove(pos + value_len, pos + len, str_len - (pos - str) - len + 1);
	memcpy(pos, value, value_len);
	str_len += replace_len;
	str[str_len] = '\0';
}
/**
 * my_strtok - string tokenizing function
 * @str: pointer to string
 * @delim: delimeter pointer
 * Return: 0 on sucsess
 */

char *my_strtok(char *str, const char *delim)
{
	static char *next_token;
	 char *token_end = str + strcspn(str, delim);

	/* If str is not provided, continue from the previous token */
	if (str == NULL)
		str = next_token;
	/* Skip leading delimiter characters */
	str += strspn(str, delim);
	/* If we have reached the end or there are no more tokens, return NULL */
	if (*str == '\0')
		return (NULL);
	/* Find the end of the token */
	token_end = str + strcspn(str, delim);	
	/* If the token_end is not at the end of the string, replace it with null */
	if (*token_end != '\0')
	{
		*token_end = '\0';
		next_token = token_end + 1;
	}
	else
	{
		next_token = token_end;
	}
	return (str);
}
