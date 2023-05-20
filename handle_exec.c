#include "shell.h"

void handle_exec(char *command_path, char *args[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execv(command_path, args);
        perror("execv");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        // Set the exit status of the last command
        set_last_command_status(WEXITSTATUS(status));
    }
}

