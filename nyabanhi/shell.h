#ifndef SHELL_H
#define SHELL_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALIASES 100
#define BUFFER_SIZE 1024
#define MAX_ARGS 64

void replace_variable(char **args, const char *variable, const char *value);
char *check_command(char *command);
int set_env(char *args[]);
int unset_env(char *args[]);
void exit_shell();
int cd(char *args[]);
int main(void);
void handle_command(char **args);
void execute_command(char **args);
#endif /* SHELL_H */
