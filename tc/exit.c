#include "shell.h"

void handle_exit(char *cmd) {
    // Remove "exit" from the command
    char *status_str = cmd + 4;

    // Remove leading spaces
    while (*status_str == ' ') {
        status_str++;
    }

    // Convert status string to integer
    int status = atoi(status_str);

    exit(status);
}
