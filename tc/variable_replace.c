#include "shell.h"

void replace_variables(char *command) {
    char variable[MAX_VARIABLE_LENGTH]; // Variable name
    char *pos; // Position of $ or $$
    char value[MAX_ALIAS_LENGTH]; // Value of the variable
    int len; // Length of the variable name

    // Find and replace $ variables
    pos = strchr(command, '$');
    while (pos != NULL) {
        // Check for special variables $?
        if (pos[1] == '?') {
            snprintf(variable, sizeof(variable), "%d", last_command_status);
            len = 2;
        } else if (pos[1] == '$') { // Check for special variables $$
            snprintf(variable, sizeof(variable), "%d", getpid());
            len = 2;
        } else {
            // Extract variable name
            sscanf(pos + 1, "%[^ \t\n]", variable);
            len = strlen(variable) + 1;
        }

        // Find the corresponding value for the variable
        get_variable_value(variable, value, sizeof(value));

        // Replace the variable with its value
        replace_string(command, pos, len, value);

        // Move to the next occurrence of $
        pos = strchr(pos + strlen(value), '$');
    }
}

