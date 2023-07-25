#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define BUFFER_SIZE 1024
#define MAX_COMMANDS 20

extern char **environ;

void parse_cmd(char *cmd, char **args);
int execute_command(const char *command, char *const args[]);
char *get_command_path(const char *command);
void execute_env(void);
void execute_exit(const char *status);
void execute_setenv(const char *variable, const char *value);
void execute_unsetenv(const char *variable);
void execute_cd(const char *directory);
char *my_getline(void);
void parse_args(char *cmd, char **args);

#endif /* SHELL_H */

