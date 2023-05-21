#include "shell.h"

void handle_cd(char *cmd) {
    // Remove "cd" from the command
    char *dir = cmd + 3;

    // Remove leading spaces
    while (*dir == ' ') {
        dir++;
    }

    // Check if no argument is given to cd
    if (*dir == '\0') {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: No $HOME variable set\n");
            return;
        }
        dir = home;
    } else if (strcmp(dir, "-") == 0) {
        // Handle "cd -" to change to the previous directory
        char *prev_dir = getenv("OLDPWD");
        if (prev_dir == NULL) {
            fprintf(stderr, "cd: No previous directory\n");
            return;
        }
        dir = prev_dir;
    }


    // Update the environment variable PWD before changing directory
    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("cd");
        return;
    }
    if (chdir(dir) == -1) {
        perror("cd");
        return;
    }

    // Update the environment variable PWD after changing directory
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("cd");
	return;
    }
    if (setenv("PWD", current_dir, 1) == -1) {
        perror("cd");
        return;
    }
}
