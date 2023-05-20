#include "shell.h"

// Structure to store an alias
typedef struct {
    char name[MAX_ALIAS_LENGTH];
    char value[MAX_ALIAS_LENGTH];
} Alias;

Alias alias_list[MAX_ALIASES]; // Array to store aliases
int num_aliases = 0; // Counter for number of aliases

void handle_alias(char *cmd) {
    if (cmd == NULL) {
        // Print all aliases
        // alias: Prints a list of all aliases, one per line, in the form name='value'
        for (int i = 0; i < num_aliases; i++) {
            printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
        }
    } else {
        // Parse the command to get alias names and values
        char *token = strtok(cmd, " ");
        while (token != NULL) {
            // Check if the token contains '=' to determine if it's an assignment
            char *equal_sign = strchr(token, '=');
            if (equal_sign != NULL) {
                // Token is an assignment, extract name and value
                *equal_sign = '\0'; // Replace '=' with null terminator
                char *name = token;
                char *value = equal_sign + 1;

                // Find if the alias already exists
                int alias_index = -1;
                for (int i = 0; i < num_aliases; i++) {
                    if (strcmp(alias_list[i].name, name) == 0) {
                        alias_index = i;
                        break;
                    }
                }

                // Add or update the alias
                if (alias_index != -1) {
                    // Alias already exists, update its value
                    strncpy(alias_list[alias_index].value, value, MAX_ALIAS_LENGTH - 1);
                    alias_list[alias_index].value[MAX_ALIAS_LENGTH - 1] = '\0';
                } else {
                    // Alias doesn't exist, add it to the list
                    if (num_aliases < MAX_ALIASES) {
                        strncpy(alias_list[num_aliases].name, name, MAX_ALIAS_LENGTH - 1);
                        alias_list[num_aliases].name[MAX_ALIAS_LENGTH - 1] = '\0';
                        strncpy(alias_list[num_aliases].value, value, MAX_ALIAS_LENGTH - 1);
                        alias_list[num_aliases].value[MAX_ALIAS_LENGTH - 1] = '\0';
                        num_aliases++;
                    } else {
                        printf("Maximum number of aliases reached\n");
                    }
                }
            } else {
                // Token is just an alias name, print its value
                // alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
                int alias_found = 0;
                for (int i = 0; i < num_aliases; i++) {
                    if (strcmp(alias_list[i].name, token) == 0) {
                        printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
                        alias_found = 1;
                        break;
                    }
                }
                if (!alias_found) {
                    printf("Alias not found: %s\n", token);
                }
            }
            token = strtok(NULL, " ");
        }
    }
}

