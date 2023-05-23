#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **argv) {
    char *prompt = "#HomeShell:~ $ ";
    char *cmd = NULL;
    size_t len = 0;
    ssize_t az;
    int i;
    char *err_msg = "No such file or directory";

    if (ac == 2) {
        // Open the file
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        // Read and execute commands from the file
        while ((az = getline(&cmd, &len, file)) != -1) {
            // Remove newline character from input
            i = az - 1;
            cmd[az - 1] = '\0';

            // Parse and execute the command
            // ...

            // Reset cmd and len for the next iteration
            cmd = NULL;
            len = 0;
        }

        // Close the file
        fclose(file);
    } else {
        // Interactive mode
        while (1) {
            // Read user input
            write(STDOUT_FILENO, prompt, strlen(prompt));
            az = getline(&cmd, &len, stdin);

            // Process user input
            // ...
        }
    }

    // Free allocated memory
    free(cmd);

    return 0;
}

