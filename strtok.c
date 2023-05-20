#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
void parse_input(char* input, char** tokens, int* num_tokens) {
    *num_tokens = 0;
    char* token = strtok(input, " \n");
    while (token != NULL && *num_tokens < MAX_NUM_TOKENS) {
        tokens[(*num_tokens)++] = token;
        token = strtok(NULL, " \n");
    }
}
int main() {
    char input[MAX_INPUT_SIZE];
    char *tokens[MAX_NUM_TOKENS];
    int num_tokens;
    int status_code = 0;
    while (1) {
        write(STDOUT_FILENO, "$ ", 2);
        read(STDIN_FILENO, input, MAX_INPUT_SIZE);
        parse_input(input, tokens, &num_tokens);
        if (num_tokens == 0) {
            continue;
        }
        if (strcmp(tokens[0], "exit") == 0) {
            if (num_tokens > 1) {
                status_code = atoi(tokens[1]);
            }
            exit(status_code);
        }
        // Handle other commands...
    }
    return 0;
}















