#include "shell.h"
#include <string.h>

// Function to replace a portion of a string with a new value
/*void replace_string(char *str, char *pos, int len, const char *value)*/

/*void replace_string(char *str, char *pos, int len, char *value)
{
    int value_len = strlen(value);
    int str_len = strlen(str);
    int replace_len = value_len - len;

    // Move the remaining portion of the string to make room for the new value
	memmove((void*)(pos + value_len), (void*)(pos + len), str_len - (pos - str) - len + 1); 

    // Copy the new value into the string at the specified position
    memcpy((void*)pos, (const void*)value, value_len);

    // Update the length of the string
    str_len += replace_len;
    str[str_len] = '\0';
}
*/
char* my_strtok(char* str, const char* delim) {
    static char* next_token = NULL;
    char* token;

    // If str is not provided, continue from the previous token
    if (str == NULL)
        str = next_token;

    // Skip leading delimiter characters
    str += strspn(str, delim);

    // If we have reached the end or there are no more tokens, return NULL
    if (*str == '\0')
        return NULL;

    // Find the end of the token
    char* token_end = str + strcspn(str, delim);

    // If the token_end is not at the end of the string, replace it with null
    if (*token_end != '\0') {
        *token_end = '\0';
        next_token = token_end + 1;
    } else {
        next_token = token_end;
    }

    return str;
}

