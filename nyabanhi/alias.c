#include "shell.h"

typedef struct {
    char *name;
    char *value;
} Alias;

Alias aliases[MAX_ALIASES];
int numAliases = 0;

/**
 * print_aliases - Print all aliases in the desired format.
 */
void print_aliases(void)
{
    for (int i = 0; i < numAliases; i++)
    {
        write(STDOUT_FILENO, aliases[i].name, strlen(aliases[i].name));
        write(STDOUT_FILENO, "='", 2);
        write(STDOUT_FILENO, aliases[i].value, strlen(aliases[i].value));
        write(STDOUT_FILENO, "'\n", 2);
    }
}

/**
 * find_alias - Find an alias by name.
 * @name: The name of the alias to find.
 * Return: Pointer to the found alias, or NULL if not found.
 */
Alias *find_alias(char *name)
{
    for (int i = 0; i < numAliases; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            return &aliases[i];
        }
    }
    return NULL;
}

/**
 * add_alias - Add or modify an alias.
 * @name: The name of the alias.
 * @value: The value of the alias.
 */
void add_alias(char *name, char *value)
{
    if (numAliases >= MAX_ALIASES)
    {
        write(STDERR_FILENO, "alias: Maximum number of aliases exceeded\n", 43);
        return;
    }

    Alias *alias = find_alias(name);
    if (alias != NULL)
    {
        free(alias->value);
        alias->value = strdup(value);
    }
    else
    {
        alias = &aliases[numAliases++];
        alias->name = strdup(name);
        alias->value = strdup(value);
    }
}

/**
 * remove_alias - Remove an alias by name.
 * @name: The name of the alias to remove.
 */
void remove_alias(char *name)
{
    Alias *alias = find_alias(name);
    if (alias != NULL)
    {
        free(alias->name);
        free(alias->value);
        *alias = aliases[--numAliases];
    }
}

/**
 * handle_alias - Handle the logic for the alias command.
 * @args: The array of command arguments.
 */
void handle_alias(char **args)
{
    if (args[1] == NULL)
    {
        print_aliases();
        return;
    }

    int i = 1;
    while (args[i] != NULL)
    {
        char *name = args[i];
        char *value = strchr(args[i], '=');

        if (value == NULL)
        {
            Alias *alias = find_alias(name);
            if (alias != NULL)
            {
                write(STDOUT_FILENO, alias->name, strlen(alias->name));
                write(STDOUT_FILENO, "='", 2);
                write(STDOUT_FILENO, alias->value, strlen(alias->value));
                write(STDOUT_FILENO, "'\n", 2);
            }
        }
        else
        {
            *value = '\0';
            value++;

            add_alias(name, value);
        }

        i++;
    }
}

/**
 * unalias - Remove aliases by name.
 * @args: The array of command arguments.
 */
void unalias(char **args)
{
    int i = 1;
    while (args[i] != NULL)
    {
        remove_alias(args[i]);
        i++;
    }
}
