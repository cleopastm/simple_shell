#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get(void) {
    extern char **environ; // Access the environment variables

    for (char **env = environ; *env != NULL; env++) {
        char *variable = *env;
        write(STDOUT_FILENO, variable, strlen(variable));
        write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}

