#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <signal.h>
#include <stdarg.h>
#include <fcntl.h>
#include <ctype.h>


#define _ALIAS_H_

#define MAX_ALIAS_LENGTH 100

typedef struct {
    char name[MAX_ALIAS_LENGTH];
    char value[MAX_ALIAS_LENGTH];
} Alias;

#define READ_SIZE 1024
#define BUFFER_SIZE 1024
#define MAX_PATH_LENGTH 1024
#define MAX_ARGUMENTS 100
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_INPUT_SIZE 1024
#define MAX_ALIAS_LENGTH 100
#define MAX_ALIASES 50
#define MAX_VARIABLE_LENGTH 100
#define MAX_VARIABLES 50

typedef struct {
    char name[MAX_VARIABLE_LENGTH];
    char value[MAX_VARIABLE_LENGTH];
} Variable;

extern int last_command_status;

int main(void); /*int ac, char **argv);*/
void parse_cmd(char *cmd, char **args);
char *get_command_path(char *command);
char *my_getline(void);
int shell_loop(void);
void print_env(void);
char *my_strtok(char *str, const char *delim);
void handle_exit(char *command);
void parse_input(char *input);
void handle_ls(char **tokens /*int num_tokens*/);
void handle_exec(char *command_path, char *args[]);
void handle_exit(char *cmd);
void handle_cd(char **tokens, int num_tokens, char *previous_dir, int *previous_dir_set);
void handle_alias(char *cmd);
void replace_string(char *str, char *pos, int len, const char *value);
/*void replace_variables(char *command, Variable *variables, int num_variables);*/
void replace_variables(char *command);
int get_last_command_status();
void set_last_command_status(int status);
char* trim_whitespace(char* str);


#endif
