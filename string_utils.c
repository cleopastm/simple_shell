#include <ctype.h>
#include "shell.h"
char* trim_whitespace(char *str) {
    // Trim leading whitespaces
    while (isspace((unsigned char)*str)) {
        str++;
    }
    // Trim trailing whitespaces
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
    return str;
}
