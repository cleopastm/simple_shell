#include "shell.h"


void parse_input(char *input)
{
	// Ignore lines starting with '#'
	if (input[0] == '#')
	{
		return;
	}
}

/*void replace_variables(char *command)
{
	char *pos; // Position of the variable
	char variable[MAX_ALIAS_LENGTH]; // Variable name
	char *value; // Value of the variable

	// Replace $? with the exit status of the last command
	while ((pos = strstr(command, "$?")) != NULL)
	{
		snprintf(variable, sizeof(variable), "%d", get_last_command_status());
		value = variable;
		replace_string(command, pos, 2, value);
	}
	
	// Replace $$ with the process ID of the shell
	while ((pos = strstr(command, "$$")) != NULL)
	{
		snprintf(variable, sizeof(variable), "%d", getpid());
		value = variable;
		replace_string(command, pos, 2, value);
	}
}
*/
/*void replace_string(char *str, char *pos, int len, char *value)
{
	int value_len = strlen(value);
	int new_len = strlen(str) - len + value_len;
	// Shift the string to the right to make room for the replacement value
	memmove(pos + value_len, pos + len, new_len - (pos - str));
	// Copy the replacement value into the string
	memcpy(pos, value, value_len);
}*/
