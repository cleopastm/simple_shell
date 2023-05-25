#include "shell.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * handle_alias - Handles alias commands
 * @cmd: The command string
 *
 * This function handles the alias command by setting and displaying aliases.
 * If no command is provided, it displays all defined aliases.
 *
 * Return: void
 */
void handle_alias(char *cmd)
{ 
	Alias alias_list[MAX_ALIASES];
	int num_aliases = 0;
	int i;
	char *name;
	char *value;
	int alias_index;
	if (cmd == NULL)
	{
	for (i = 0; i < num_aliases; i++)
	{
	char buffer[BUFFER_SIZE];
	int ret = snprintf(buffer, BUFFER_SIZE, "%s='%s'\n", alias_list[i].name, alias_list[i].value);
	if (ret < 0 || ret >= BUFFER_SIZE)
	{
	write(STDERR_FILENO, "Error: Failed to write alias\n", strlen("Error: Failed to write alias\n"));
	return;
	}
	write(STDOUT_FILENO, buffer, ret);
	}
	}
	else
	{
	char *token = strtok(cmd, " ");
	while (token != NULL)
	{
	char *equal_sign = strchr(token, '=');
	if (equal_sign != NULL)
	{
	*equal_sign = '\0';
	name = token;
	value = equal_sign + 1;
	alias_index = -1;
	for (i = 0; i < num_aliases; i++)
	{
	if (strcmp(alias_list[i].name, name) == 0)
	{
	alias_index = i;
	break;
	}
	}
	if (alias_index != -1)
	{
	strncpy(alias_list[alias_index].value, value, MAX_ALIAS_LENGTH - 1);
	alias_list[alias_index].value[MAX_ALIAS_LENGTH - 1] = '\0';
	}
	else
	{
	if (num_aliases < MAX_ALIASES)
	{
	strncpy(alias_list[num_aliases].name, name, MAX_ALIAS_LENGTH - 1);
	alias_list[num_aliases].name[MAX_ALIAS_LENGTH - 1] = '\0';
	strncpy(alias_list[num_aliases].value, value, MAX_ALIAS_LENGTH - 1);
	alias_list[num_aliases].value[MAX_ALIAS_LENGTH - 1] = '\0';
	num_aliases++;
	}
	else
	{
	write(STDERR_FILENO, "Maximum number of aliases reached\n", strlen("Maximum number of aliases reached\n"));
	return;
	}
	}
	}
	else
	{
	int alias_found = 0;
	for (i = 0; i < num_aliases; i++)
	{
	if (strcmp(alias_list[i].name, token) == 0)
	{
        char buffer[BUFFER_SIZE];
	int ret = snprintf(buffer, BUFFER_SIZE, "%s='%s'\n", alias_list[i].name, alias_list[i].value);
	if (ret < 0 || ret >= BUFFER_SIZE)
	{
	write(STDERR_FILENO, "Error: Failed to write alias\n", strlen("Error: Failed to write alias\n"));
	return;
	}
	write(STDOUT_FILENO, buffer, ret);
	alias_found = 1;
	break;
	}
	}
	if (!alias_found)
	{
	char buffer[BUFFER_SIZE];
	int ret = snprintf(buffer, BUFFER_SIZE, "Alias not found: %s\n", token);
	if (ret < 0 || ret >= BUFFER_SIZE)
	{
	write(STDERR_FILENO, "Error: Failed to write alias\n", strlen("Error: Failed to write alias\n"));
	return;
	}
	write(STDOUT_FILENO, buffer, ret);
	}
	}
	token = strtok(NULL, " ");
	}
	}
}
