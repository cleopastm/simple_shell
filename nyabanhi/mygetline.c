#include "shell.h"

/**
 * my_getline - Custom getline function to read a line from the user
 *
 * Return: Pointer to the read line
 */
char *my_getline(void)
{
    static char buffer[BUFFER_SIZE];
    static ssize_t characters_remaining = 0;
    static ssize_t buffer_index = 0;

    if (characters_remaining <= 0)
    {
        characters_remaining = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        buffer_index = 0;

        if (characters_remaining <= 0)
            return NULL;
    }

    char *line = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (line == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    ssize_t line_index = 0;
    char current_char;

    while (buffer_index < characters_remaining)
    {
        current_char = buffer[buffer_index++];
        line[line_index++] = current_char;

        if (current_char == '\n')
        {
            line[line_index] = '\0';
            return line;
        }
    }

    // If the line does not fit within the buffer, reallocate the line buffer
    if (line_index >= BUFFER_SIZE)
    {
        size_t new_size = line_index + 1;
        char *new_line = (char *)realloc(line, new_size * sizeof(char));
        if (new_line == NULL)
        {
            perror("realloc error");
            exit(EXIT_FAILURE);
        }

        line = new_line;
    }

    characters_remaining = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    buffer_index = 0;

    if (characters_remaining <= 0)
    {
        line[line_index] = '\0';
        if (line_index == 0)
        {
            free(line);
            return NULL;
        }
        else
        {
            return line;
        }
    }

    return line;
}

